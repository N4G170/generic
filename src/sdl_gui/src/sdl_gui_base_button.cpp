#include "sdl_gui_base_button.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"
#include "sdl_gui_log.hpp"
#include <memory>

namespace sdl_gui
{

BaseButton::BaseButton(GuiMainPointers main_pointers, const Position& position, const Dimensions& size) : GuiElement{main_pointers, position, size},
    m_box_texture{m_main_pointers.resource_manager_ptr->GetTexture(c_img_white_dot)}
{
    AddGuiCollider({0,0}, Size(), &m_transform);


    m_state_transitions.emplace(ButtonState::ACTIVE, ButtonStateTransition{nullptr, {255,255,255,255}});
    m_state_transitions.emplace(ButtonState::INACTIVE, ButtonStateTransition{nullptr, {255,255,255,128}});
    m_state_transitions.emplace(ButtonState::OVER, ButtonStateTransition{nullptr, {200,200,200,255}});
    m_state_transitions.emplace(ButtonState::PRESSED, ButtonStateTransition{nullptr, {145,145,145,255}});

    m_mouse_interaction.MouseButtonCallback(SDL_BUTTON_LEFT, InputKeyCallbackType::DOWN, std::bind(&BaseButton::ButtonTransitionCallback, this, std::ref(m_state_transitions[ButtonState::PRESSED])));
    m_mouse_interaction.MouseCallback(MouseCallbackType::OVER, std::bind(&BaseButton::ButtonTransitionCallback, this, std::ref(m_state_transitions[ButtonState::OVER])));
}

BaseButton::~BaseButton() noexcept
{

}

BaseButton::BaseButton(const BaseButton& other): GuiElement{other}, m_box_texture{other.m_box_texture}
{
    //manual copy because std::unique_ptr cannot be copied
    for(auto& transition : other.m_state_transitions)
    {
        SDL_Rect source = *transition.second.source_rect_ptr.get();
        m_state_transitions.emplace(transition.first, ButtonStateTransition{std::unique_ptr<SDL_Rect>(&source), transition.second.colour});
    }
}

BaseButton::BaseButton(BaseButton&& other) noexcept : GuiElement{other}
{
    if(&other != this)
    {
        m_state_transitions = std::move(other.m_state_transitions);
        m_box_texture = std::move(other.m_box_texture);
        m_mouse_interaction = std::move(other.m_mouse_interaction);
    }
}

BaseButton& BaseButton::operator=(const BaseButton& other)
{
    if(this != &other)//not same ref
    {
        BaseButton tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

BaseButton& BaseButton::operator=(BaseButton&& other) noexcept
{
    if(&other != this)
    {
        m_state_transitions = std::move(other.m_state_transitions);
        m_box_texture = std::move(other.m_box_texture);
        m_mouse_interaction = std::move(other.m_mouse_interaction);
    }

    return *this;
}

//<f> Overrides GUIElement
void BaseButton::Input(const SDL_Event& event)
{
    if( !m_active )
    return;

    m_mouse_interaction.Input(event, m_colliders);
}

void BaseButton::ClearInput()
{
    m_mouse_interaction.ClearInput();
}

void BaseButton::Logic(float delta_time)
{
    if(m_active)//btn is active
    {
        ButtonTransitionCallback(m_state_transitions[ButtonState::ACTIVE]);

        m_mouse_interaction.Logic(delta_time);
    }
    else
        ButtonTransitionCallback(m_state_transitions[ButtonState::INACTIVE]);
}

void BaseButton::Render(float delta_time)
{
    Render(delta_time, m_main_pointers.main_camera_ptr);
}

void BaseButton::Render(float delta_time, Camera* camera)
{
    if(!m_render)
        return;

    SDL_Rect dst{RenderRect()};

    //apply camera position
    if(!m_transform.ParentViewport())//if inside viewport we cant add camera position
    {
        dst.x += camera->CameraPosition().x;
        dst.y += camera->CameraPosition().y;
    }

    if(camera->RectInsideCamera(dst))
        m_box_texture.Render(m_current_source_rect, &dst);
}
//</f>

//<f> Virtual Methods
void BaseButton::SetStateColour(ButtonState button_state, const SDL_Colour& colour)
{
    m_state_transitions[button_state].colour = colour;
}

void BaseButton::SetStateColours(const SDL_Colour& inactive, const SDL_Colour& active, const SDL_Colour& over, const SDL_Colour& pressed)
{
    m_state_transitions[ButtonState::INACTIVE].colour = inactive;
    m_state_transitions[ButtonState::ACTIVE].colour = active;
    m_state_transitions[ButtonState::OVER].colour = over;
    m_state_transitions[ButtonState::PRESSED].colour = pressed;
}

void BaseButton::SetStateTextureSrcRect(ButtonState button_state, const SDL_Rect& rect)
{
    m_state_transitions[button_state].source_rect_ptr.reset(new SDL_Rect{rect});
}

void BaseButton::SetStateTextureSrcRect(const SDL_Rect& inactive, const SDL_Rect& active, const SDL_Rect& over, const SDL_Rect& pressed)
{
    m_state_transitions[ButtonState::INACTIVE].source_rect_ptr.reset(new SDL_Rect{inactive});
    m_state_transitions[ButtonState::ACTIVE].source_rect_ptr.reset(new SDL_Rect{active});
    m_state_transitions[ButtonState::OVER].source_rect_ptr.reset(new SDL_Rect{over});
    m_state_transitions[ButtonState::PRESSED].source_rect_ptr.reset(new SDL_Rect{pressed});
}
//</f>

//<f> Getters/Setters

//</f>

void BaseButton::ButtonTransitionCallback(const ButtonStateTransition& transition)
{
    m_box_texture.ColourModulation(transition.colour);
    m_current_source_rect = transition.source_rect_ptr.get();
}
}
