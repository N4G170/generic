#include "particles_state.hpp"
#include "constants.hpp"
#include "particle_emitter.hpp"
#include "image.hpp"

//<f> Constructors & operator=
ParticleState::ParticleState(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr) :
    StateInterface(state_machine, state_name, system_manager_ptr)
{

}

ParticleState::~ParticleState() noexcept
{

}

ParticleState::ParticleState(const ParticleState& other) : StateInterface(other)
{

}

ParticleState::ParticleState(ParticleState&& other) noexcept: StateInterface(std::move(other))
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
            case SDLK_r: m_emitter->CreateParticle(); break;
        }
    }
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
void ParticleState::Render(SDL_Renderer* renderer_ptr, float delta_time)
{

}

void ParticleState::Enter()
{
    auto emitter_obj{m_system_manager_ptr->Objects()->CreateObject()};
    m_emitter = new ParticleEmitter{m_system_manager_ptr};
    emitter_obj->AddScript(m_emitter);
    m_emitter->CreateParticle();
}

void ParticleState::Exit()
{
    m_system_manager_ptr->Clear();
}
//</f>

void ParticleState::BackToMenuCallback()
{
    m_state_machine_ptr->ChangeState(StateName::Menu);
}
