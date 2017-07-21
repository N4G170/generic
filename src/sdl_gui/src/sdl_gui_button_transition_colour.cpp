#include "sdl_gui_button_transition_colour.hpp"
#include <utility>
#include "sdl_gui_constants.hpp"

namespace sdl_gui
{

//<f> Constructors & operator=
ButtonTransitionColour::ButtonTransitionColour(ResourceManager* resource_manager_ptr): m_texture{resource_manager_ptr->GetTexture(c_img_white_dot)}, m_current_colour{255,255,255,255}
{
    m_state_colours.emplace(ButtonState::ACTIVE, SDL_Colour{255,255,255,255});
    m_state_colours.emplace(ButtonState::INACTIVE, SDL_Colour{255,255,255,255});
    m_state_colours.emplace(ButtonState::OVER, SDL_Colour{255,255,255,128});
    m_state_colours.emplace(ButtonState::PRESSED, SDL_Colour{128,128,128,255});
}

ButtonTransitionColour::~ButtonTransitionColour() noexcept {}

ButtonTransitionColour::ButtonTransitionColour(const ButtonTransitionColour& other): m_texture{other.m_texture}, m_current_colour{other.m_current_colour},
    m_state_colours{other.m_state_colours} {}

ButtonTransitionColour::ButtonTransitionColour(ButtonTransitionColour&& other) noexcept: m_texture{std::move(other.m_texture)}, m_current_colour{std::move(other.m_current_colour)},
    m_state_colours{std::move(other.m_state_colours)} {}

ButtonTransitionColour& ButtonTransitionColour::operator=(const ButtonTransitionColour& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

ButtonTransitionColour& ButtonTransitionColour::operator=(ButtonTransitionColour&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_texture = std::move(other.m_texture);
        m_current_colour = std::move(other.m_current_colour);
        m_state_colours = std::move(other.m_state_colours);
    }
    return *this;
}
//</f>

//<f> Virtual Methods
void ButtonTransitionColour::Render(const SDL_Rect& dst)
{
    SDL_Rect destination{dst};
    m_texture.Render(nullptr, &destination);
}

void ButtonTransitionColour::ChangeState(ButtonState state)
{
    m_texture.ColourModulation(m_state_colours[state]);
}
//</f>

//<f> Getters/Setters
void ButtonTransitionColour::SetStateColour(ButtonState state, const SDL_Colour& colour)
{
    m_state_colours[state] = colour;
}

void ButtonTransitionColour::SetStateColour(const SDL_Colour& inactive, const SDL_Colour& active, const SDL_Colour& over, const SDL_Colour& pressed)
{
    SetStateColour(ButtonState::INACTIVE, inactive);
    SetStateColour(ButtonState::ACTIVE, active);
    SetStateColour(ButtonState::OVER, over);
    SetStateColour(ButtonState::PRESSED, pressed);
}
//</f>

}//namespace
