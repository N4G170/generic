#include "sdl_gui_container_box.hpp"
#include "sdl_gui_constants.hpp"
#include <utility>

namespace sdl_gui
{

ContainerBox::ContainerBox(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions):
    GuiElement{position, dimensions}, IGuiRender{renderer_ptr, resource_manager_ptr},
    m_element_dimensions{0,0}, m_vertical_element_spacing{0}, m_horizontal_element_spacing{0}, m_top_margin{0}, m_bottom_margin{0}, m_left_margin{0}, m_right_margin{0},
    m_render_background{true}, m_background{m_resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    AddGuiCollider({0,0}, m_transform.Size(), &m_transform);
}

ContainerBox::~ContainerBox() noexcept
{

}

ContainerBox::ContainerBox(const ContainerBox& other)
{

}

ContainerBox::ContainerBox(ContainerBox&& other) noexcept
{

}

ContainerBox& ContainerBox::operator=(const ContainerBox& other)
{
    if(this != &other)//not same ref
    {
        ContainerBox tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ContainerBox& ContainerBox::operator=(ContainerBox&& other) noexcept
{
    return *this;
}

//<f> Virtual methods override
void ContainerBox::Logic(float fixed_delta_time)
{
    for(std::unique_ptr<GuiElement>& element : m_gui_elements)
        element->Logic(fixed_delta_time);
}

void ContainerBox::Render(float delta_time)
{
    //set viewport
    SDL_Rect dst {this->TransformPtr()->RenderRect()};
    SDL_RenderSetViewport(m_renderer_ptr, &dst);

    if(m_render_background)
    {
        m_background.Render();
    }

    for(IGuiRender*& element : m_gui_renderable)
        element->Render(delta_time);

    //reset viewport
    SDL_RenderSetViewport(m_renderer_ptr, nullptr);
    SDL_RenderDrawRect(m_renderer_ptr, &dst);
}
void ContainerBox::RenderBorder(float delta_time)
{
    SDL_Rect border{m_transform.RenderRect()};
    SDL_SetRenderDrawColor(m_renderer_ptr, m_border_colour.r, m_border_colour.g, m_border_colour.b, m_border_colour.a);
    SDL_RenderDrawRect(m_renderer_ptr, &border);
}

void ContainerBox::Input(const SDL_Event& event)
{
    if(!MouseInsideCollider(event.motion.x, event.motion.y))
    {
        for(IGuiInteraction*& interactable : m_gui_interactables)
            interactable->ClearInput();
    }
    else
    {
        for(IGuiInteraction*& interactable : m_gui_interactables)
            interactable->Input(event);
    }
}

//</f>

//<f> Contents management
void ContainerBox::AddElement(GuiElement* element, IGuiRender* renderable, IGuiInteraction* interactable)
{
    element->TransformPtr()->Parent(this->TransformPtr());
    element->TransformPtr()->ParentViewport(this->TransformPtr());

    m_gui_elements.push_back(std::unique_ptr<GuiElement>{element});
    m_gui_renderable.push_back(renderable);

    if(interactable)
        m_gui_interactables.push_back(interactable);

    //update internal positioning
    UpdateElementsPositions();
}
//</f>

void ContainerBox::UpdateElementsPositions()
{
    for(unsigned int i{0}; i < m_gui_elements.size(); ++i)
    {
        Position tmp_position{m_gui_elements[i]->TransformPtr()->LocalPosition()};
        // Dimensions tmp_dimensions{m_gui_elements[i]->TransformPtr()->Size()};

        tmp_position.x = m_left_margin;
        //sum margin with spacing and the height of previous element
        tmp_position.y = m_top_margin + m_vertical_element_spacing * i + (i==0 ? 0 : m_gui_elements[i-1]->TransformPtr()->Size().h) * i;

        m_gui_elements[i]->TransformPtr()->LocalPosition(tmp_position);
    }
}

}//namespace
