#include "sdl_gui_element.hpp"
#include "sdl_gui_interaction.hpp"
#include "sdl_gui_texture.hpp"
#include "sdl_gui_enums.hpp"
#include <vector>

namespace sdl_gui
{
    #ifndef SDL_GUI_CONTAINER_BOX_HPP
    #define SDL_GUI_CONTAINER_BOX_HPP

    class ContainerBox: public GuiElement, public GuiInteraction
    {
        public:
            /* Default constructor */
            ContainerBox(ResourceManager* resource_manager_ptr, SDL_Renderer* renderer_ptr, Position position, Dimensions dimensions);
            /* Default destructor */
            virtual ~ContainerBox() noexcept;

            /* Copy constructor */
            ContainerBox(const ContainerBox& other);
            /* Move constructor */
            ContainerBox(ContainerBox&& other) noexcept;

            /* Copy operator */
            ContainerBox& operator= (const ContainerBox& other);
            /* Move operator */
            ContainerBox& operator= (ContainerBox&& other) noexcept;

            //<f> Virtual methods override
            void Logic(float fixed_delta_time);
            void Render(float delta_time);
            void Render(SDL_Renderer* renderer_ptr, float delta_time);

            void Input(const SDL_Event& event);
            //</f>

            //<f> Contents management
            /**
             * Add a new element to this container
             * @param element      A pointer to the element to be added. The pointer will be managed by the container so DO NOT DELETE IT
             * @param interactable If the element expects user inputs cast to its parent class GuiInteraction is expected. If nullptr nothing is done. Also DO NOT DELETE IT
             */
            void AddElement(GuiElement* element, GuiInteraction* interactable = nullptr);
            //</f>

            //<f> Background
            bool RenderBackground() const { return m_render_background; }
            void RenderBackground(bool render_background) { m_render_background = render_background; }
            //</f>

        private:
            //<f> Elements
            std::vector<std::unique_ptr<GuiElement>> m_gui_elements;
            std::vector<GuiInteraction*> m_gui_interactables;

            Dimensions m_element_dimensions;
            int m_vertical_element_spacing;
            int m_horizontal_element_spacing;
            int m_top_margin;
            int m_bottom_margin;
            int m_left_margin;
            int m_right_margin;

            void UpdateElementsPositions();
            //</f>

            //<f> Background
            bool m_render_background;
            Texture m_background;
            //</f>
    };

    #endif //SDL_GUI_CONTAINER_BOX_HPP
}//namespace
