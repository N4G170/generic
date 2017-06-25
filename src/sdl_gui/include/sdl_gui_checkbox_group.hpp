#include "sdl_gui_checkbox.hpp"
#include "sdl_gui_render.hpp"
#include "sdl_gui_interaction.hpp"
#include <functional>
#include "sdl_gui_enums.hpp"

namespace sdl_gui
{

#ifndef SDL_GUI_CHECKBOX_GROUP_HPP
#define SDL_GUI_CHECKBOX_GROUP_HPP

class CheckBoxGroup : public GuiElement, public IGuiRender, public IGuiInteraction
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        CheckBoxGroup(SDL_Renderer* renderer_ptr, ResourceManager* resource_manager_ptr, Position position, Dimensions dimensions);
        /* Default destructor */
        virtual ~CheckBoxGroup() noexcept;

        /* Copy constructor */
        CheckBoxGroup(const CheckBoxGroup& other);
        /* Move constructor */
        CheckBoxGroup(CheckBoxGroup&& other) noexcept;

        /* Copy operator */
        CheckBoxGroup& operator= (const CheckBoxGroup& other);
        /* Move operator */
        CheckBoxGroup& operator= (CheckBoxGroup&& other) noexcept;
        //</f>

        //<f> Overrides IGuiInteraction
        virtual void Input(const SDL_Event& event);
        //</f>

        //<f> Overrides GuiElement
        virtual void Logic(float delta_time);
        //</f>

        //<f> Overrides IGuiRender
        virtual void Render(float delta_time);
        virtual void RenderBorder(float delta_time);
        //</f>

        //<f> Virtual Methods
        virtual int AddCheckBox(CheckBox* checkbox);
        //</f>

        //<f> Getters/Setters

        //</f>

        //<f> Callbacks
        std::function<void(std::vector<CheckBox*>& selected_values)> ValuesChanged;
        //</f>

    protected:
        // vars and stuff
        CheckBoxGroupType m_group_type;

        std::map<int, std::unique_ptr<CheckBox>> m_checkboxes;

        std::vector<CheckBox*> m_selected_values;

        void ChildValueChanged(CheckBox* changed_checkbox);
};

#endif //SDL_GUI_CHECKBOX_GROUP_HPP

}//namespace
