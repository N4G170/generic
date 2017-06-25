#include "SDL.h"
#include <list>
#include <functional>
#include <string>
#include "sdl_gui_transform.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_resource_manager.hpp"

#include "sdl_gui_uid.hpp"

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
        GuiElement(Position local_position, Dimensions dimensions);
        /* Default constructor */
        GuiElement();
        /* Default destructor */
        virtual ~GuiElement() noexcept;

        /* Copy constructor */
        GuiElement(const GuiElement& other);
        /* Move constructor */
        GuiElement(GuiElement&& other) noexcept;

        GuiElement& operator= (const GuiElement& other);

        GuiElement& operator= (GuiElement&& other);
        //</f>

        //<f> Virtual Funtions
        virtual void FixedLogic(float fixed_delta_time);
        virtual void Logic(float delta_time);
        //</f>

        //<f> Getters/Setters
        UID ElementUID() const { return m_uid; }
        GuiTransform* TransformPtr() { return &m_transform; }
        //</f>

        //<f> Transform Interface
        /**
         * Sets this element parent. Will, also, set the parent in the transform
         */
        void Parent(GuiElement* parent);
        //</f>

    protected:
        // vars and stuff
        UID m_uid;
        GuiTransform m_transform;
        std::string m_name;
        // AnchorType m_anchor_type;

        /**
        * Called internally by Add Parent
        */
        void AddChild(GuiElement* child);
        void RemoveChild(UID child_uid);
};

#endif //GUI_ELEMENT_HPP

}//namespace
