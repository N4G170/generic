#include <vector>
#include "SDL.h"
#include "sdl_gui_uid.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_TRANSFORM_HPP
#define SDL_GUI_TRANSFORM_HPP

struct Position
{
    int x, y, z;
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
        //<f> Constructors and operator=
        /* Default constructor */
        explicit GuiTransform(UID owner_uid);
        /* Default destructor */
        virtual ~GuiTransform() noexcept;

        /* Copy constructor */
        GuiTransform(const GuiTransform& other);

        GuiTransform(const GuiTransform& other, UID owner_uid);
        /* Move constructor */
        GuiTransform(GuiTransform&& other) noexcept;

        /* Copy operator */
        GuiTransform& operator= (const GuiTransform& other);
        /* Move operator */
        GuiTransform& operator= (GuiTransform&& other) noexcept;
        //</f>

        //<f>Getters / Setters > */
        Position GlobalPosition() const;
        void GlobalPosition(const Position& new_global_position);
        Position LocalPosition() const { return m_local_position; };
        void LocalPosition(const Position& new_local_position);

        void Size(const Dimensions& new_size);
        Dimensions Size() const { return m_size; };

        void ParentViewport(GuiTransform* parent_viewport);
        bool ParentViewport() const { return m_parent_viewport; };

        virtual void Parent(GuiTransform* parent);
        GuiTransform* Parent() const;

        UID OwnerUID() const { return m_uid; };
        //</f>

        /**
        * Calculates the position and dimensions for the rendering. The position is ajusted to account for the existence or not of a parent viewport (as it has a new origin).
        * \return SDL_Rect with rendering position and dimensions
        */
        SDL_Rect RenderRect();

    private:
        // vars and stuff
        /**
         * UID of the owner instance
         */
        UID m_uid;

        /**
         * Position of the elemtn in the world
         */
        Position m_global_position;

        /**
         * Position of the element relative to its parent. parent == nullptr ? global_position : local_position
         */
        Position m_local_position;//reltive to parent. Same as global if no parent

        /**
         * Bounds dimensions of the element
         */
        Dimensions m_size;

        /**
         * Pointer to the viewport in which this element is. nullptr if element is in the world
         */
        GuiTransform* m_parent_viewport;

        /**
         * Pointer to parent element. nullptr if element is directly in the world
         */
        GuiTransform* m_parent;

        /**
         * List of all the children elements of this one
         */
        std::vector<GuiTransform*> m_children;

        void AddChild(GuiTransform* child);
        void RemoveChild(UID child_uid);

        void RecalculateGlobalPosition();
        void RecalculateLocalPosition();
};

#endif //GUI_TRANSFORM_HPP

}//namespace
