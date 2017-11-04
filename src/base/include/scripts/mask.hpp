#ifndef MASK_HPP
#define MASK_HPP

#include "render_script.hpp"
#include "SDL.h"
#include "custom_texture.hpp"
#include "system_manager.hpp"
#include "image.hpp"

class Mask : public RenderScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Mask(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~Mask() noexcept;

        /** brief Copy constructor */
        Mask(const Mask& other);
        /** brief Move constructor */
        Mask(Mask&& other) noexcept;

        /** brief Copy operator */
        Mask& operator= (const Mask& other);
        /** brief Move operator */
        Mask& operator= (Mask&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Render(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        void SetImage(Image* image);
        Image* GetImage() const;

        SDL_Colour ClearColour() const;
        void ClearColour(const SDL_Colour& colour);
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        SystemManager* m_system_manager;

        CustomTexture m_bg_texture;
        Image* m_mask_image;
        SDL_Colour m_clear_colour;
    private:
};

#endif //MASK_HPP
