#include <SDL2/SDL.h>
#include <list>

namespace sdl_gui
{

#ifndef GUI_ELEMENT_HPP
#define GUI_ELEMENT_HPP

enum AnchorType
{
    TOP_LEFT,
    TOP_CENTRE,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTRE,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTRE,
    BOTTOM_RIGHT
};

struct Position { int x, y; };
struct Dimensions { int w, h; };

class GuiElement
{
    public:
        GuiElement(SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
        /* Default constructor */
        GuiElement();
        /* Default destructor */
        virtual ~GuiElement() noexcept;

        /* Copy constructor */
        GuiElement(const GuiElement& other);
        /* Move constructor */
        GuiElement(GuiElement&& other) noexcept;

        /* Copy operator */
        GuiElement& operator= (const GuiElement& other);
        /* Move operator */
        GuiElement& operator= (GuiElement&& other) noexcept;

        /* < Pure Virtual Funtions > */
        virtual void Render() = 0;
        virtual void Render(SDL_Renderer* renderer) = 0;
        virtual void Logic() = 0;
        /* </ Pure Virtual Funtions > */



        /* < Getters / Setters > */
        void X(int x){ m_position.x = x; }
        int X() const { return m_position.x; }
        void Y(int y){ m_position.y = y; }
        int Y() const { return m_position.y; }

        void Width(int width){ m_dimensions.w = width; }
        int Width() const { return m_dimensions.w; }
        void Height(int height){ m_dimensions.h = height; }
        int Height() const { return m_dimensions.h; }

        void ZIndex(int z_index){ m_zindex = z_index; }
        int ZIndex() const { return m_zindex; }
        /* </ Getters / Setters > */

    protected:
        // vars and stuff
        Position m_position;
        Dimensions m_dimensions;
        // AnchorType m_anchor_type;
        int m_zindex;

        SDL_Renderer* m_renderer_ptr;

        // GuiElement* m_parent;
        // std::list<GuiElement*> m_children;
};

#endif //GUI_ELEMENT_HPP

}//namespace
