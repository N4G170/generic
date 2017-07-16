#include "sdl_gui_element.hpp"
#include "sdl_gui_base_button.hpp"
#include "sdl_gui_button.hpp"
#include "sdl_gui_checkbox_group.hpp"
#include "sdl_gui_checkbox.hpp"
#include "sdl_gui_image.hpp"
#include "sdl_gui_label.hpp"
#include "sdl_gui_layout.hpp"
#include "sdl_gui_progress_bar.hpp"
#include "sdl_gui_slider.hpp"
#include "sdl_gui_textbox.hpp"

namespace sdl_gui
{
#ifndef SDL_GUI_MANAGER_HPP
#define SDL_GUI_MANAGER_HPP

class GuiManager
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        GuiManager();
        /* Default destructor */
        virtual ~GuiManager() noexcept;

        /* Copy constructor */
        GuiManager(const GuiManager& other);
        /* Move constructor */
        GuiManager(GuiManager&& other) noexcept;

        /* Copy operator */
        GuiManager& operator= (const GuiManager& other);
        /* Move operator */
        GuiManager& operator= (GuiManager&& other) noexcept;
        //</f>

        //<f> Element Virtual Calls
        void Input(const SDL_Event& event);

        void FixedLogic(float fixed_delta_time);
        void Logic(float delta_time);

        void Render(float delta_time);
        //</f>

        //<f> Element Management

        /**
         * \brief Create a new element to be managed by the manager. Returns a pointer to said element
         */
        template<typename T>
        T* CreateElement(const GuiMainPointers& main_pointers, const Position& position, const Dimensions& size)
        {
            T* element = new T{main_pointers, position, size};
            m_elements.emplace(element->ElementUID(), element);
            return dynamic_cast<T*>(m_elements[element->ElementUID()].get());
        }

        /**
         * \brief Creates a pointer to an element of type 'T'.
         * \nYOU ARE RESPONSIBLE FOR MANAGING IT
         */
        template<typename T>
        T* CreateFreeElement(const GuiMainPointers& main_pointers, const Position& position, const Dimensions& size)
        {
            return new T {main_pointers, position, size};
        }

        /**
         * \brief Release and element from the management by the manager and return a dynamic_cast<T*>(pointer) to it.\n
         * Returns nullptr if case of failure
         */
        template<typename T>
        T* ReleaseElement(UID uid)
        {
            auto find_result{m_elements.find(uid)};
            if(find_result != std::end(m_elements))//found element
            {
                auto tmp_ptr{m_elements[uid].release()};//release pointer from unique_ptr
                m_elements.erase(uid);//remove from hash table

                return dynamic_cast<T*>(tmp_ptr);
            }
            return nullptr;
        }

        /**
         * \brief Deletes an element from the manager.\n
         * CAUTION: make sure you clear any pointer to it as it will no longer be valid
         */
        void DeleteElement(UID uid);

        void ClearElementsInput();

        //</f>
    private:
        // vars and stuff
        std::unordered_map<UID, std::unique_ptr<GuiElement>> m_elements;
};

#endif //GUI_MANAGER_HPP
}//namespace
