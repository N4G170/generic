#ifndef MAP_DEMO_HPP
#define MAP_DEMO_HPP

#include <vector>
#include "sdl_gui_label.hpp"
#include "state_interface.hpp"
#include "cell.hpp"
#include "army.hpp"
#include "infobox.hpp"

class MapDemo : public StateInterface
{
    enum LabelsId
    {
        TITLE,
        MOUSE_POSITION,
        CURRENT_CELL,
        SELECTED_CELL,
        ARMY,
        NAVY,
        BR1,
        BR2,
        BR3,
        BR4,
        BR5,
        BR6,
        L1,
        L2,
        L3,
        L4,
        BACK,
    };

    public:
        MapDemo(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, sdl_gui::ResourceManager* resource_manager_ptr);
        ~MapDemo();
        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&);

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float fixed_frame_time = 1);

        /**
         * \brief Render the state visual elements
         */
        virtual void Render(SDL_Renderer*, float delta_time);

        //Callbacks
        void CellMouseHover(int cell_index);
        void CellMouseClick(int cell_index);

        //void ArmyMouseHover();
        void ArmyMouseClick();

    private:
        Infobox m_infobox;
        std::vector<Cell> m_map;
        Transform m_origin;

        SDL_Rect m_outter_box{30,30,1440,940};
        SDL_Rect m_inner_box{50,50,1400,900};
        Transform m_inner_box_viewport;
        bool m_mouse_inside_viewport;

        int m_cell_width;
        int m_cell_height;
        int m_map_width_cell_count;
        int m_map_height_cell_count;
        int m_map_width;
        int m_map_height;

        bool mid=false;
        float m_scale;

        //Callbacks flags and stuff
        int m_mouse_hover_cell_index;
        int m_selected_cell_index;

        //armies
        Army m_player_army;
        bool m_army_selected;
};

#endif //MAP_DEMO_HPP
