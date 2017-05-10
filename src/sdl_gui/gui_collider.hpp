#include <SDL2/SDL.h>
#include <functional>
#include <vector>
#include "gui_transform.hpp"

namespace sdl_gui
{

#ifndef GUI_COLLIDER_HPP
#define GUI_COLLIDER_HPP


enum GuiColliderShapeType
{
    BOX,
    CIRCLE,
};

class GuiColliderShape
{
    public:
        explicit GuiColliderShape(const SDL_Rect& collider_dimensions);
        GuiColliderShape(int centre_x, int centre_y, int circle_radius);
        virtual ~GuiColliderShape();
        GuiColliderShape(const GuiColliderShape& other);
        GuiColliderShape(GuiColliderShape&& other);
        GuiColliderShape& operator= (const GuiColliderShape& other);
        GuiColliderShape& operator= (GuiColliderShape&& other);

        std::function<bool(int,int)> IsPointColliding;
    // protected:
        GuiColliderShapeType m_type;

        SDL_Rect m_rect_collider;

        Position m_circle_centre;
        int m_circle_collider_radius;
        int m_squared_radius;        

        void SetCollisionDetectionFunction();
        bool BoxPointCollision(int mouse_x, int mouse_y);
        bool CirclePointCollision(int mouse_x, int mouse_y);
};

class GuiCollider
{
    public:
        /* Box constructor */
        explicit GuiCollider(const SDL_Rect& collider_dimensions);
        /* Circle constructor */
        GuiCollider(int centre_x, int centre_y, int circle_radius);

        /* Default destructor */
        virtual ~GuiCollider() noexcept;

        /* Copy constructor */
        GuiCollider(const GuiCollider& other);
        /* Move constructor */
        GuiCollider(GuiCollider&& other) noexcept;

        /* Copy operator */
        GuiCollider& operator= (const GuiCollider& other);
        /* Move operator */
        GuiCollider& operator= (GuiCollider&& other) noexcept;

        bool IsPointColliding(int mouse_x, int mouse_y);
        // std::function<bool(int,int)> IsPointColliding;

        void SetColliderShape(const SDL_Rect& collider_dimensions);
        void SetColliderShape(int centre_x, int centre_y, int circle_radius);

        void ProcessFlags();
        std::function<void()> MouseEnterCallBack;
        std::function<void()> MouseInCallBack;
        std::function<void()> MouseExitCallBack;

    // private:
        // vars and stuff
        std::vector<GuiColliderShape> m_shapes;

        bool m_previous_mouse_in;
        bool m_mouse_in;
};

#endif //GUI_COLLIDER_HPP
}//namespace
