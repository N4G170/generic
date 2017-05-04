#include "SDL2/SDL.h"

namespace sdl_ui
{

#ifndef GUI_RENDER_HPP
#define GUI_RENDER_HPP

class GuiRender
{
    public:
        /* Default constructor */
        GuiRender();
        /* Default destructor */
        virtual ~GuiRender() noexcept;

        /* Copy constructor */
        GuiRender(const GuiRender& other);
        /* Move constructor */
        GuiRender(GuiRender&& other) noexcept;

        /* Copy operator */
        GuiRender& operator= (const GuiRender& other);
        /* Move operator */
        GuiRender& operator= (GuiRender&& other) noexcept;

        virtual void Render(SDL_Renderer*) = 0;

    private:
        // vars and stuff
};

#endif //GUI_RENDER_HPP
}
