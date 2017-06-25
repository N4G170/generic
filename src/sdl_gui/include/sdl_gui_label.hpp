#include <string>
#include "SDL2/SDL.h"
#include "sdl_gui_element.hpp"
#include "sdl_gui_render.hpp"
#include "sdl_gui_local_texture.hpp"
#include "sdl_gui_font.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_LABEL_HPP
#define SDL_GUI_LABEL_HPP

class Label : public GuiElement, public IGuiRender
{
    public:
        /* Default constructor */
        // Label();

        Label(SDL_Renderer* renderer, ResourceManager* resource_manager_ptr, const std::string& font_path, int font_size, const std::string& text, const SDL_Colour& text_colour, Position position);
        Label(SDL_Renderer* renderer, ResourceManager* resource_manager_ptr, Font* font_ptr, const std::string& text, const SDL_Colour& text_colour, Position position);

        /* Default destructor */
        virtual ~Label() noexcept;

        /* Copy constructor */
        Label(const Label& other);
        /* Move constructor */
        Label(Label&& other) noexcept;

        /* Copy operator */
        Label& operator= (const Label& other);
        /* Move operator */
        Label& operator= (Label&& other) noexcept;

        //<f> Overrides GuiElement
        virtual void Logic(float delta_time);
        //</f>

        //<f> Overrides IGuiRender
        virtual void Render(float delta_time);
        //</f>

        //<f> Getters/Setters
        std::string Text();
        virtual void Text(const std::string& text, const SDL_Colour& text_colour);

        int LineLength() const { return m_line_length; }
        void LineLength(int line_length);
        //</f>

    private:
        /**
         * \brief Texture with the text to be rendered
         */
        LocalTexture m_text_texture;
        /**
         * \brief The std::string being rendered
         */
        std::string m_text;

        /**
         * \brief Color of the text
         */
        SDL_Colour m_text_colour;

        /**
         * \brief Pointer to the TTF font being used
         */
        Font* m_font_ptr;

        /**
         * Max line length allowed
         */
        int m_line_length;
};

#endif //LABEL_HPP

}//namespace
