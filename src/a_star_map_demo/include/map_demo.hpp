#ifndef MAP_DEMO_HPP
#define MAP_DEMO_HPP

#include <vector>
#include "state_interface.hpp"
#include "map.hpp"

class MapDemo : public StateInterface
{
    public:
        MapDemo(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr);
        ~MapDemo();
        /**
         * \brief Precess SDL user input
         */
        void Input(const SDL_Event&) override;

        /**
         * \brief Process any logic, runs after input
         */
        void Logic(float fixed_frame_time = 1) override;

        void FixedLogic(float fixed_delta_time) override {}

        /**
         * \brief Render the state visual elements
         */
        void Render(SDL_Renderer*, float delta_time) override;

        void Enter() override;
        void Exit() override;

    private:
        Map* m_map_script;
        // Infobox m_infobox;
        // std::vector<Cell> m_map;
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
        // Army m_player_army;
        bool m_army_selected;
};

#endif //MAP_DEMO_HPP
