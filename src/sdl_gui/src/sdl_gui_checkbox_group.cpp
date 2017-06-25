#include "sdl_gui_checkbox_group.hpp"
#include <utility>
#include "sdl_gui_log.hpp"

namespace sdl_gui
{

//<f> Constructors & operator=
CheckBoxGroup::CheckBoxGroup(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions):
    GuiElement{position, dimensions}, IGuiRender{renderer_ptr, resource_manager_ptr}, m_group_type{CheckBoxGroupType::MULTIPLE}
{

}

CheckBoxGroup::~CheckBoxGroup() noexcept
{

}

CheckBoxGroup::CheckBoxGroup(const CheckBoxGroup& other) : GuiElement{other}, IGuiRender{other}, IGuiInteraction{other},
    m_group_type{other.m_group_type}, m_selected_values{other.m_selected_values}
{
    for(auto& checkbox : other.m_checkboxes)
        m_checkboxes.emplace( std::make_pair(checkbox.first, std::unique_ptr<CheckBox>(new CheckBox(*checkbox.second.get()))) );
}

CheckBoxGroup::CheckBoxGroup(CheckBoxGroup&& other) noexcept : GuiElement{other}, IGuiRender{other}, IGuiInteraction{other},
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
    GuiElement::operator=(other);
    IGuiRender::operator=(other);
    IGuiInteraction::operator=(other);

    this->m_group_type = std::move(other.m_group_type);
    this->m_checkboxes = std::move(other.m_checkboxes);
    this->m_selected_values = std::move(other.m_selected_values);

    for(auto& checkbox : m_checkboxes)
        checkbox.second->ValueChanged = std::bind(&CheckBoxGroup::ChildValueChanged, this, std::placeholders::_1);

    return *this;
}
//</f>

//<f> Overrides IGuiInteraction
void CheckBoxGroup::Input(const SDL_Event& event)
{
    if(!m_active)
        return;

    for(auto& checkbox : m_checkboxes)
        checkbox.second->Input(event);
}
//</f>

//<f> Overrides GuiElement
void CheckBoxGroup::Logic(float delta_time)
{
    for(auto& checkbox : m_checkboxes)
        checkbox.second->Logic(delta_time);
}
//</f>

//<f> Overrides IGuiRender
void CheckBoxGroup::Render(float delta_time)
{
    if(!m_render)
        return;

    for(auto& checkbox : m_checkboxes)
        checkbox.second->Render(delta_time);
}

void CheckBoxGroup::RenderBorder(float delta_time)
{
    SDL_Rect border{m_transform.RenderRect()};
    SDL_SetRenderDrawColor(m_renderer_ptr, m_border_colour.r, m_border_colour.g, m_border_colour.b, m_border_colour.a);
    SDL_RenderDrawRect(m_renderer_ptr, &border);
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
