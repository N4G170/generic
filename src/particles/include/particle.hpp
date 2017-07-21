#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "SDL.h"
#include "sdl_gui_resource_manager.hpp"

class Particle
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Particle(SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr);
        /** brief Default destructor */
        virtual ~Particle() noexcept;

        /** brief Copy constructor */
        Particle(const Particle& other);
        /** brief Move constructor */
        Particle(Particle&& other) noexcept;

        /** brief Copy operator */
        Particle& operator= (const Particle& other);
        /** brief Move operator */
        Particle& operator= (Particle&& other) noexcept;
        //</f>

        //<f> Virtual Methods

        //</f>

        //<f> Methods
        void Logic(float delta_time);
        void FixedLogic(float fixed_delta_time);
        void Render(float delta_time);
        //</f>

        //<f> Getters/Setters

        //</f>

    protected:
        // vars and stuff
        SDL_Texture* m_particle_texture;

    private:
};

#endif //PARTICLE_HPP
