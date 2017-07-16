#include "SDL.h"
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include "sdl_gui_transform.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_resource_manager.hpp"
#include "sdl_gui_camera.hpp"

#include "sdl_gui_uid.hpp"
#include "sdl_gui_collider.hpp"
#include <tuple>

namespace sdl_gui
{

#ifndef SDL_GUI_ELEMENT_HPP
#define SDL_GUI_ELEMENT_HPP

/**
 * Definition of the most basic gui element, containing virtual logic functions and the transform
 */
class GuiElement
{
    public:
        //<f> Constructors & operator=
        GuiElement(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
        /* Default destructor */
        virtual ~GuiElement() noexcept;

        /**
         * \brief Copy constructor. Will generate new uid for the copy
         */
        GuiElement(const GuiElement& other);
        /* Move constructor */
        GuiElement(GuiElement&& other) noexcept;

        GuiElement& operator= (const GuiElement& other);

        GuiElement& operator= (GuiElement&& other);

        bool operator==(const GuiElement& other){ return m_uid == other.m_uid; }
        //</f>

        //<f> Virtual Methods
        virtual void Input(const SDL_Event& event);
        virtual void ClearInput();

        virtual void FixedLogic(float fixed_delta_time);
        virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
        //</f>

        //<f> Render
        SDL_Rect RenderRect();
        //</f>

        //<f> Getters/Setters
        UID ElementUID() const { return m_uid; }
        GuiTransform* TransformPtr() { return &m_transform; }
        Camera* GuiCamera() const { return m_main_pointers.main_camera_ptr; }
        //</f>

        //<f> Position, Size & Transform interface
        Position GlobalPosition() const { return m_transform.GlobalPosition(); }
        void GlobalPosition(const Position& new_global_position) { m_transform.GlobalPosition(new_global_position); }
        Position LocalPosition() const { return m_transform.LocalPosition(); }
        void LocalPosition(const Position& new_local_position) { m_transform.LocalPosition(new_local_position); }

        void ParentViewport(GuiTransform* parent_viewport) { m_transform.ParentViewport(parent_viewport); }
        bool ParentViewport() const { return m_transform.ParentViewport(); }

        void Size(const Dimensions& new_size) { m_size = new_size; }
        Dimensions Size() const { return m_size; }

        void CentreInParent();
        //</f>

        //<f> Interaction & Colliders
        /* Add Box collider */
        void AddGuiCollider(const Position& local_position, const Dimensions& size, GuiTransform* owner_transform);
        /* Add Circle collider */
        void AddGuiCollider(const Position& local_position, int circle_radius, GuiTransform* owner_transform);
        //</f>

        //<f> Parent & Children
        /**
         * Sets this element parent. Will, also, set the parent in the transform
         */
        void Parent(GuiElement* parent);
        GuiElement* Parent() const { return m_parent; }
        std::unordered_map<UID, GuiElement*>* Children() { return &m_children; }
        //</f>

    protected:
        // vars and stuff
        //<f> ID, Position and Size
        UID m_uid;
        GuiTransform m_transform;
        /**
         * Render dimensions of the element
         */
        Dimensions m_size;
        //</f>

        //<f> Render
        /**
         * \brief Pointers for external resources needed. EX: renderer, camera, resource_manager
         */
        GuiMainPointers m_main_pointers;

        /**
         * True - render element
         * False - Do not render
         */
        bool m_render;
        //</f>

        //<f> Interaction
        std::vector<Collider> m_colliders;
        bool m_active;
        bool m_focused;
        //</f>

        //<f> Parent & Children
        GuiElement* m_parent;
        std::unordered_map<UID, GuiElement*> m_children;

        /**
         * \brief Take ownership of the element
         */
        void AddChild(GuiElement* element);

        void RemoveChild(UID uid);
        //</f>
};

#endif //GUI_ELEMENT_HPP

}//namespace
