#include "sdl_gui_checkbox_group.hpp"
#include <utility>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

//<f> Constructors & operator=
CheckBoxGroup::CheckBoxGroup(GuiMainPointers main_pointers, const Position& position, const Dimensions& size):
    GuiElement{main_pointers, position, size}, m_group_type{CheckBoxGroupType::MULTIPLE}
{

}

CheckBoxGroup::~CheckBoxGroup() noexcept
{

}

CheckBoxGroup::CheckBoxGroup(const CheckBoxGroup& other) : GuiElement{other},
    m_group_type{other.m_group_type}, m_selected_values{other.m_selected_values}
{
    for(auto& checkbox : other.m_checkboxes)
    {
        auto ptr{std::unique_ptr<CheckBox>(new CheckBox(*checkbox.second.get()))};
        ptr->ValueChanged = std::bind(&CheckBoxGroup::ChildValueChanged, this, std::placeholders::_1);
        m_checkboxes.emplace( std::make_pair(checkbox.first, std::move(ptr)) );
    }
}

CheckBoxGroup::CheckBoxGroup(CheckBoxGroup&& other) noexcept : GuiElement{other},
    m_group_type{std::move(other.m_group_type)}, m_checkboxes{std::move(other.m_checkboxes)}, m_selected_values{std::move(other.m_selected_values)}
{
    for(auto& checkbox : m_checkboxes)
        checkbox.second->ValueChanged = std::bind(&CheckBoxGroup::ChildValueChanged, this, std::placeholders::_1);
}

CheckBoxGroup& CheckBoxGroup::operator=(const CheckBoxGroup& other)
{
    if(this != &other)//not same ref
    {
        CheckBoxGroup tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

CheckBoxGroup& CheckBoxGroup::operator=(CheckBoxGroup&& other) noexcept
{
    if(this != &other)
    {
        GuiElement::operator=(other);

        this->m_group_type = std::move(other.m_group_type);
        this->m_checkboxes = std::move(other.m_checkboxes);
        this->m_selected_values = std::move(other.m_selected_values);

        for(auto& checkbox : m_checkboxes)
            checkbox.second->ValueChanged = std::bind(&CheckBoxGroup::ChildValueChanged, this, std::placeholders::_1);
    }
    return *this;
}
//</f>

//<f> Overrides GuiElement
void CheckBoxGroup::Input(const SDL_Event& event)
{
    if(!m_active)
        return;

    for(auto& checkbox : m_checkboxes)
        checkbox.second->Input(event);
}

void CheckBoxGroup::Logic(float delta_time)
{
    for(auto& checkbox : m_checkboxes)
        checkbox.second->Logic(delta_time);
}

void CheckBoxGroup::Render(float delta_time)
{
    Render(delta_time, m_main_pointers.main_camera_ptr);
}

void CheckBoxGroup::Render(float delta_time, Camera* camera)
{
    if(!m_render)
        return;

    for(auto& checkbox : m_checkboxes)
        checkbox.second->Render(delta_time);
}

//</f>

//<f> Virtual Methods
int CheckBoxGroup::AddCheckBox(CheckBox* checkbox)
{
    static int checkbox_id{0};

    ++checkbox_id;

    m_checkboxes.emplace( std::make_pair(checkbox_id, std::unique_ptr<CheckBox>(checkbox)) );

    m_checkboxes[checkbox_id]->ValueChanged = std::bind(&CheckBoxGroup::ChildValueChanged, this, std::placeholders::_1);

    return checkbox_id;
}
//</f>

void CheckBoxGroup::ChildValueChanged(CheckBox* changed_checkbox)
{
    if(m_group_type == CheckBoxGroupType::MULTIPLE)
    {
        m_selected_values.push_back(changed_checkbox);
        if(ValuesChanged)
            ValuesChanged(m_selected_values);
    }
    else
    {

    }
}

}//namespace
