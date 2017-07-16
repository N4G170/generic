#include "sdl_gui_element.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_utils.hpp"
#include <unordered_map>

namespace sdl_gui
{
#ifndef SDL_GUI_LAYOUT_HPP
#define SDL_GUI_LAYOUT_HPP

struct LayoutConfig
{
    LayoutWrapMode wrap_mode;
    Dimensions element_size;
    int num_of_lines;
    int num_of_columns;
    int vertical_element_spacing;
    int horizontal_element_spacing;
    int top_margin;
    int bottom_margin;
    int left_margin;
    int right_margin;
    std::string ToString()
    {
        return sdl_gui::ToString(element_size)+" "+std::to_string(num_of_lines)+" "+std::to_string(num_of_columns);
    }
};

class Layout: public GuiElement
{
    public:
        /* Default constructor */
        Layout(GuiMainPointers main_pointers, const Position& position, const Dimensions& size);
        /* Default destructor */
        virtual ~Layout() noexcept;

        /* Copy constructor */
        Layout(const Layout& other);
        /* Move constructor */
        Layout(Layout&& other) noexcept;

        /* Copy operator */
        Layout& operator= (const Layout& other);
        /* Move operator */
        Layout& operator= (Layout&& other) noexcept;

        //<f> Overrides GuiElement
        // virtual void Input(const SDL_Event& event);

        // virtual void FixedLogic(float fixed_delta_time);
        // virtual void Logic(float delta_time);

        virtual void Render(float delta_time);
        virtual void Render(float delta_time, Camera* camera);
        //</f>

        //<f> Contents management
        /**
         * \brief Add a new element to this container.
         */
        void AddElement(GuiElement* element);

        void RemoveElement(UID uid);

        LayoutConfig Config() const { return m_layout_config; }
        void Config(const LayoutConfig& config){ m_layout_config = config; }
        //</f>

    private:
        //<f> Elements
        std::unordered_map<UID, GuiElement*> m_elements;

        LayoutConfig m_layout_config;


        void UpdateElementsPositions();
        //</f>

};

#endif //SDL_GUI_LAYOUT_HPP
}//namespace
