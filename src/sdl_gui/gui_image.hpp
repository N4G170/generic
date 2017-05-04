#include <SDL2/SDL.h>
#include "gui_element.hpp"
#include <string>

namespace sdl_gui
{

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

class GuiImage : public GuiElement
{
    public:
        /* Base constructor */
        GuiImage(SDL_Renderer* renderer_ptr, const std::string& texture_path, Position position);
        /* Default destructor */
        virtual ~GuiImage() noexcept;

        /* Copy constructor */
        GuiImage(const GuiImage& other);
        /* Move constructor */
        GuiImage(GuiImage&& other) noexcept;

        /* Copy operator */
        GuiImage& operator= (const GuiImage& other);
        /* Move operator */
        GuiImage& operator= (GuiImage&& other) noexcept;

        /* < Overrides GUIElement > */
        void Render();
        void Render(SDL_Renderer* renderer);
        void Logic();
        /* </ Overrides > */

    private:
        // vars and stuff
        SDL_Texture* m_texture;
};

#endif //GUI_IMAGE_HPP

}//namespace
