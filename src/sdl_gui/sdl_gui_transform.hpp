#include <vector>
#include <SDL2/SDL.h>
#include "sdl_gui_uid.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_TRANSFORM_HPP
#define SDL_GUI_TRANSFORM_HPP

struct Position
{
    int x, y;
    bool operator == (const Position& other){ return other.x == x && other.y == y; }
    bool operator != (const Position& other){ return other.x != x || other.y != y; }
    Position operator + (const Position& other){ return *this += other; }
    Position& operator += (const Position& other){ this->x += other.x; this->y += other.y; return *this; }
    Position operator - (const Position& other){ return *this -= other; }
    Position& operator -= (const Position& other){ this->x -= other.x; this->y -= other.y; return *this; }
};

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
        Position GlobalPosition() const;
        void GlobalPosition(const Position& new_global_position);
        Position LocalPosition() const { return m_local_position; };
        void LocalPosition(const Position& new_local_position);

        void BaseDimensions(const Dimensions& new_dimensions);
        Dimensions BaseDimensions() const { return m_dimensions; };

        void ParentViewport(GuiTransform* parent_viewport);
        bool ParentViewport() const { return m_parent_viewport; };

        SDL_Rect RenderRect();
        // void SetPosition(int x, int y);

        // void Width(int width){ m_dimensions.w = width; }
        // int Width() const { return m_dimensions.w; }
        // void Height(int height){ m_dimensions.h = height; }
        // int Height() const { return m_dimensions.h; }

        virtual void Parent(GuiTransform* parent);
        GuiTransform* Parent() const;
        void AddChild(GuiTransform* child);
        void RemoveChild(UID child_uid);

        UID TransformUID() const { return m_uid; };
        /* </ Getters / Setters > */
    private:
        // vars and stuff
        UID m_uid;
        Position m_global_position;
        Position m_local_position;//reltive to parent. Same as global if no parent
        Dimensions m_dimensions;

        GuiTransform* m_parent_viewport;
        GuiTransform* m_parent;
        std::vector<GuiTransform*> m_children;

        void RecalculateGlobalPosition();
        void RecalculateLocalPosition();
};

#endif //GUI_TRANSFORM_HPP

}//namespace
