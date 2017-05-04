#include <string>
#include "SDL2/SDL.h"
#include "gui_element.hpp"
#include "font.hpp"

namespace sdl_gui
{

#ifndef LABEL_HPP
#define LABEL_HPP

class Label : public GuiElement
{
    public:
        /* Default constructor */
        Label();

        Label(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& text, const SDL_Colour& text_colour, Position position, Dimensions dimensions);

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

        /* < Overrides GUIElement > */
        void Render();
        void Render(SDL_Renderer* renderer);
        void Logic();
        /* </ Overrides > */

        std::string Text();
        void Text(const std::string& text, SDL_Colour text_colour);

    private:
        /**
         * \brief Texture with the text to be rendered
         */
        SDL_Texture* m_text_texture;
        SDL_Texture* m_bg_texture;
        /**
         * \brief The std::string being rendered
         */
        std::string m_text;

        /**
         * \brief Color of the text
         */
        SDL_Colour m_text_colour;
        SDL_Colour m_bg_colour;

        /**
         * \brief Pointer to the TTF font being used
         */
        Font* m_font_ptr;
};

#endif //LABEL_HPP

}//namespace
