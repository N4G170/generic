#include "sdl_gui_element.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_label.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_TEXTBOX_HPP
#define SDL_GUI_TEXTBOX_HPP

class Textbox : public GuiElement
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        Textbox(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
        /* Default destructor */
        virtual ~Textbox() noexcept;

        /* Copy constructor */
        Textbox(const Textbox& other);
        /* Move constructor */
        Textbox(Textbox&& other) noexcept;

        /* Copy operator */
        Textbox& operator= (const Textbox& other);
        /* Move operator */
        Textbox& operator= (Textbox&& other) noexcept;
        //</f>

        //<f> Overrides GuiElement
        // virtual void Input(const SDL_Event& event);

        // virtual void FixedLogic(float fixed_delta_time);
        // virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
        //</f>

        //<f> Virtual Methods

        //</f>

        //<f> Getters/Setters

        //</f>

    protected:
        // vars and stuff
        Texture m_bg_texture;
        SDL_Rect m_edit_field_rect;

        Label m_text_label;

        void CentreLabel();
};

#endif //SDL_GUI_TEXTBOX_HPP

}//namespace
