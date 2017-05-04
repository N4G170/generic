#include <SDL2/SDL.h>
#include <functional>

namespace sdl_gui
{

#ifndef GUI_COLLIDER_HPP
#define GUI_COLLIDER_HPP

enum GuiColliderType
{
    BOX,
    CIRCLE,
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

        std::function<bool(int,int)> IsPointColliding;
        // std::function<bool(int,int)> IsPointColliding;

        void SetCollider(const SDL_Rect& collider_dimensions);
        void SetCollider(int centre_x, int centre_y, int circle_radius);

    // private:
        // vars and stuff
        GuiColliderType m_type;
        SDL_Rect m_rect_collider;
        int m_circle_collider_radius;
        int m_squared_radius;
        int m_centre_x;
        int m_centre_y;

        bool BoxPointCollision(int mouse_x, int mouse_y);
        bool CirclePointCollision(int mouse_x, int mouse_y);
};

#endif //GUI_COLLIDER_HPP
}//namespace
