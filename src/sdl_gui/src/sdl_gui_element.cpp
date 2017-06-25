#include "sdl_gui_element.hpp"
#include <utility>

namespace sdl_gui
{

GuiElement::GuiElement(Position local_position, Dimensions dimensions): m_uid{GenerateUID()}, m_transform{m_uid}
{
    m_transform.LocalPosition(local_position);
    m_transform.Size(dimensions);
}

GuiElement::GuiElement(): m_uid{GenerateUID()}, m_transform{m_uid} {}

GuiElement::~GuiElement() noexcept
{

}

GuiElement::GuiElement(const GuiElement& other) : m_uid{GenerateUID()}, m_transform{other.m_transform, m_uid} {}

GuiElement::GuiElement(GuiElement&& other) noexcept : m_transform{std::move(other.m_transform)}
{
    m_uid = std::move(other.m_uid);
}

GuiElement& GuiElement::operator= (const GuiElement& other)
{
    if(this != &other)
    {
        GuiElement tmp{other};
        *this = std::move(tmp);
    }
    return *this;
}

GuiElement& GuiElement::operator= (GuiElement&& other)
{
    if(this != &other)
    {
        this->m_uid =std::move(other.m_uid);
        this->m_transform = std::move(other.m_transform);
    }
    return *this;
}

//<f> Virtual Funtions
void GuiElement::FixedLogic(float fixed_delta_time)
{

}
void GuiElement::Logic(float delta_time)
{

}
//</f>

}//namespace
