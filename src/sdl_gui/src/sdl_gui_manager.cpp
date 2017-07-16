#include "sdl_gui_manager.hpp"
#include <utility>
#include <iostream>

namespace sdl_gui
{
//<f> Constructors & operator=
GuiManager::GuiManager()
{

}

GuiManager::~GuiManager() noexcept
{

}

GuiManager::GuiManager(const GuiManager& other)
{

}

GuiManager::GuiManager(GuiManager&& other) noexcept
{

}

GuiManager& GuiManager::operator=(const GuiManager& other)
{
    if(this != &other)//not same ref
    {
        GuiManager tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

GuiManager& GuiManager::operator=(GuiManager&& other) noexcept
{
    return *this;
}
//</f>

//<f> Element Virtual Calls
void GuiManager::Input(const SDL_Event& event)
{
    for(auto& element : m_elements)
        element.second->Input(event);
}

void GuiManager::FixedLogic(float fixed_delta_time)
{
    for(auto& element : m_elements)
        element.second->FixedLogic(fixed_delta_time);
}

void GuiManager::Logic(float delta_time)
{
    for(auto& element : m_elements)
        element.second->Logic(delta_time);
}

void GuiManager::Render(float delta_time)
{
    for(auto& element : m_elements)
        element.second->Render(delta_time);
}
//</f>

//<f> Element Management
/**
 * \brief Specialization of \see T* ReleaseElement(UID uid)
 */
template<>
GuiElement* GuiManager::ReleaseElement<GuiElement>(UID uid)
{
    auto find_result{m_elements.find(uid)};
    if(find_result != std::end(m_elements))//found element
    {
        auto tmp_ptr{m_elements[uid].release()};//release pointer from unique_ptr
        m_elements.erase(uid);//remove from hash table

        return tmp_ptr;//no cast needed for this specialization
    }
    return nullptr;
}

void GuiManager::DeleteElement(UID uid)
{
    m_elements.erase(uid);
}

void GuiManager::ClearElementsInput()
{
    for(auto& element : m_elements)
        element.second->ClearInput();
}
//</f>
}//namespace
