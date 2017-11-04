#ifndef PARTICLE_EMITTER_HPP
#define PARTICLE_EMITTER_HPP

#include "behaviour_script.hpp"
#include "object.hpp"
#include <vector>
#include "system_manager.hpp"

class ParticleEmitter: public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit ParticleEmitter(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~ParticleEmitter() noexcept;

        /** brief Copy constructor */
        ParticleEmitter(const ParticleEmitter& other);
        /** brief Move constructor */
        ParticleEmitter(ParticleEmitter&& other) noexcept;

        /** brief Copy operator */
        ParticleEmitter& operator= (const ParticleEmitter& other);
        /** brief Move operator */
        ParticleEmitter& operator= (ParticleEmitter&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        //</f> /Virtual Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

        //<f> Particle Control
        void CreateParticle();
        //</f> /Particle Control
    protected:
        // vars and stuff

    private:
    SystemManager* m_system_manager;
    std::vector<Object*> m_particles;
};

#endif //PARTICLE_EMITTER_HPP
