#include "particles_state.hpp"
#include "constants.hpp"
#include "sdl_gui_constants.hpp"

//<f> Constructors & operator=
ParticleState::ParticleState(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr) :
    StateInterface(state_machine, state_name, resource_manager_ptr), m_gui_manager{renderer_ptr, resource_manager_ptr}
{
    auto back_button = m_gui_manager.CreateElement<sdl_gui::Button>({15,15}, {150,50});
    back_button->CreateLabel("Back to Menu", sdl_gui::c_default_font_path, sdl_gui::c_default_font_size, sdl_gui::Colour::Black, {0,0});
    back_button->CentreLabel();

    back_button->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&ParticleState::BackToMenuCallback, this));
}

ParticleState::~ParticleState() noexcept
{

}

ParticleState::ParticleState(const ParticleState& other) : StateInterface(other), m_gui_manager{other.m_gui_manager}
{

}

ParticleState::ParticleState(ParticleState&& other) noexcept: StateInterface(std::move(other)), m_gui_manager{std::move(other.m_gui_manager)}
{

}

ParticleState& ParticleState::operator= (const ParticleState& other)
{
    if(this != &other)
    {
        auto tmp{other};
        *this = std::move(tmp);
    }
    return *this;
}

ParticleState& ParticleState::operator= (ParticleState&& other) noexcept
{
    if(this != &other)
    {
        m_gui_manager = std::move(other.m_gui_manager);
    }
    return *this;
}

//</f>

//<f> Interface
/**
 * \brief Precess SDL user input
 */
void ParticleState::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
        }
    }

    m_gui_manager.Input(event);
}

/**
 * \brief Process any logic, runs after input
 */
void ParticleState::Logic(float delta_time)
{
    m_gui_manager.Logic(delta_time);
}

/**
 * \brief Render the state visual elements
 */
void ParticleState::Render(SDL_Renderer* renderer_ptr, float delta_time)
{
    m_gui_manager.Render(delta_time);
}
//</f>

void ParticleState::BackToMenuCallback()
{
    m_gui_manager.ClearElementsInput();
    m_state_machine_ptr->ChangeState(StateName::Menu);
}
