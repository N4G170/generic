#include "SDL.h"
#include <functional>
#include <vector>
#include "sdl_gui_transform.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_COLLIDER_HPP
#define SDL_GUI_COLLIDER_HPP


enum ColliderShapeType
{
    BOX,
    CIRCLE,
};

class ColliderShape
{
    public:
        ColliderShape(const Position& position, const Dimensions& dimensions, GuiTransform* owner_transform);
        ColliderShape(const Position& position, int circle_radius, GuiTransform* owner_transform);
        virtual ~ColliderShape();
        ColliderShape(const ColliderShape& other);
        ColliderShape(ColliderShape&& other);
        ColliderShape& operator= (const ColliderShape& other);
        ColliderShape& operator= (ColliderShape&& other);

        std::function<bool(int,int)> IsPointColliding;

        void DebugRender(SDL_Renderer* renderer_ptr, const SDL_Colour& colour = {0,0,0,255});
    protected:
        ColliderShapeType m_type;

        //offset of the shape in relation to its owner
        Position m_local_position;

        //if shape is a rect
        Dimensions m_dimensions;

        //if shape is a circle
        int m_circle_collider_radius;
        int m_squared_radius;

        //lets us get the global position of this collider parent
        GuiTransform* m_owner_transform;

        void SetCollisionDetectionFunction();
        bool BoxPointCollision(int mouse_x, int mouse_y);
        bool CirclePointCollision(int mouse_x, int mouse_y);
};

class Collider
{
    public:
        /* Box constructor */
        Collider(const Position& position, const Dimensions& rect_collider, GuiTransform* owner_transform);
        /* Circle constructor */
        Collider(const Position& position, int circle_radius, GuiTransform* owner_transform);

        /* Default destructor */
        virtual ~Collider() noexcept;

        /* Copy constructor */
        Collider(const Collider& other);
        /* Move constructor */
        Collider(Collider&& other) noexcept;

        /* Copy operator */
        Collider& operator= (const Collider& other);
        /* Move operator */
        Collider& operator= (Collider&& other) noexcept;

        bool IsPointColliding(int mouse_x, int mouse_y);

        void SetColliderShape(const Position& position, const Dimensions& dimensions);
        void SetColliderShape(const Position& centre_position, int circle_radius);

        void DebugRender(SDL_Renderer* renderer_ptr, const SDL_Colour& colour = {0,0,0,255});

    private:
        // vars and stuff
        std::vector<ColliderShape> m_shapes;
        GuiTransform* m_owner_transform;
};

#endif //GUI_COLLIDER_HPP
}//namespace
