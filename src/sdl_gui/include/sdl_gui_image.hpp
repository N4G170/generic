#include "sdl_gui_texture.hpp"
#include "sdl_gui_local_texture.hpp"
#include "sdl_gui_element.hpp"

namespace sdl_gui
{
#ifndef SDL_GUI_IMAGE_HPP
#define SDL_GUI_IMAGE_HPP

class Image : public GuiElement
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        Image(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
        /* Default destructor */
        virtual ~Image() noexcept;

        /* Copy constructor */
        Image(const Image& other);
        /* Move constructor */
        Image(Image&& other) noexcept;

        /* Copy operator */
        Image& operator= (const Image& other);
        /* Move operator */
        Image& operator= (Image&& other) noexcept;
        //</f>

        //<f> Overrides GuiElement
        virtual void Input(const SDL_Event& event);

        virtual void FixedLogic(float fixed_delta_time);
        virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
        //</f>

        //<f> Getters/Setters

        //</f>

    protected:
        Texture m_texture;

        SDL_Rect* m_source_rect;
};

#endif //SDL_GUI_IMAGE_HPP
}//namespace
