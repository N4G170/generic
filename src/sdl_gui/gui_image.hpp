#include <SDL2/SDL.h>
#include "gui_element.hpp"
#include <string>
#include <memory>

namespace sdl_gui
{

#ifndef GUI_IMAGE_HPP
#define GUI_IMAGE_HPP

class GuiImage : public GuiElement
{
    public:
        /* Base constructor */
        GuiImage(SDL_Renderer* renderer_ptr, const std::string& texture_path);
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
        void Render(SDL_Renderer* renderer_ptr);
        void Logic();
        /* </ Overrides > */


        void SetSourceRect(SDL_Rect src_rect);
        void ClearSourceRect();
        void SetDestinationRect(SDL_Rect dst_rect);
        void ClearDestinationRect();

    private:
        // vars and stuff
        SDL_Texture* m_texture;
        std::unique_ptr<SDL_Rect> m_source_rect;
        bool m_has_destination_rect;
};

#endif //GUI_IMAGE_HPP

}//namespace
