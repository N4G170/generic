#include <vector>

namespace sdl_gui
{

#ifndef GUI_TRANSFORM_HPP
#define GUI_TRANSFORM_HPP

struct Position { int x, y; };
struct Dimensions { int w, h; };

class GuiTransform
{
    public:
        /* Default constructor */
        GuiTransform();
        /* Default destructor */
        virtual ~GuiTransform() noexcept;

        /* Copy constructor */
        GuiTransform(const GuiTransform& other);
        /* Move constructor */
        GuiTransform(GuiTransform&& other) noexcept;

        /* Copy operator */
        GuiTransform& operator= (const GuiTransform& other);
        /* Move operator */
        GuiTransform& operator= (GuiTransform&& other) noexcept;

        /* < Getters / Setters > */
        void X(int x){ m_position.x = x; }
        int X() const { return m_position.x; }
        void Y(int y){ m_position.y = y; }
        int Y() const { return m_position.y; }

        void Width(int width){ m_dimensions.w = width; }
        int Width() const { return m_dimensions.w; }
        void Height(int height){ m_dimensions.h = height; }
        int Height() const { return m_dimensions.h; }

        virtual void Parent(GuiTransform* parent){ m_parent = parent; }
        GuiTransform* Parent() const { return m_parent; }
        /* </ Getters / Setters > */

    private:
        // vars and stuff
        Position m_position;
        Dimensions m_dimensions;

        GuiTransform* m_parent;
        std::vector<GuiTransform*> m_children;

};

#endif //GUI_TRANSFORM_HPP

}//namespace
