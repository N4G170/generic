#include "particle_state.hpp"

//<f> Constructors & operator=
ParticleState::ParticleState(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr);
ParticleState::~ParticleState();

ParticleState::ParticleState(const ParticleState& other);
ParticleState::ParticleState(ParticleState&& other);

ParticleState& ParticleState::operator= (const ParticleState& other);
ParticleState& ParticleState::operator= (ParticleState&& other);

//</f>

//<f> Interface
/**
 * \brief Precess SDL user input
 */
void ParticleState::Input(const SDL_Event&)
{

}

/**
 * \brief Process any logic, runs after input
 */
void ParticleState::Logic(float delta_time)
{

}

/**
 * \brief Render the state visual elements
 */
void ParticleState::Render(SDL_Renderer*, float delta_time)
{
    
}
//</f>
