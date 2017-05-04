#ifndef ARMY_HPP
#define ARMY_HPP

#include <vector>
#include <map>
#include "object.hpp"

struct ArmyMovementCosts
{
    int m_grass_grass;
    int m_grass_hill;
    int m_hill_hill;
    int m_hill_grass;
};

class Army: public Object
{
    public:
        Army();
        virtual ~Army();

        void Input(const SDL_Event& event);
        void Logic(float fixed_frame_time);
        void Render(SDL_Renderer *renderer, float delta_time, float scale);

        void CorrectOriginPosition(float x_correction, float y_correction);

        std::function<void()> MouseHoverCallBack;
        std::function<void()> MouseClickCallBack;

    private:
        std::vector<std::map<std::string, SDL_Rect>> m_bodies;
        SDL_Colour m_faction_colour;
        int m_current_body_index;

        float m_health;
        float m_damage;

        SDL_Rect m_box_collider;
        bool m_mouse_hover;
        bool m_selected;

        int m_offset_x;
        int m_offset_y;

        //because we are inside a viewport and SDL uses a new origin here, we need to store a correction for its origin
        int m_origin_correction_x;
        int m_origin_correction_y;

        ArmyMovementCosts m_movement_costs;
};

#endif //ARMY_HPP
