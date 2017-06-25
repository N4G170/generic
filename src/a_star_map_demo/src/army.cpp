#include <algorithm>

#include "army.hpp"
#include "utils.hpp"
#include "message_writer.hpp"

Army::Army():m_current_body_index{0}, m_health{100}, m_damage{1}, m_mouse_hover{false}, m_selected{false}, m_offset_x{0}, m_offset_y{0}, m_origin_correction_x{0}, m_origin_correction_y{0}
{
    m_box_collider = {15,4,20,42};

    m_bodies.resize(15);
    int index{0};

    //idle f1
    m_bodies[index]["Head"] = {22,5,5,5};
    m_bodies[index]["Torso"] = {20,10,10,15};
    m_bodies[index]["Left_Leg"] = {20,20,3,25};
    m_bodies[index]["Right_Leg"] = {27,20,3,25};
    m_bodies[index]["Weapon"] = {17,5,2,40};
    ++index;

    //combat left
    m_bodies[index]["Head"] = {12,5,5,5};
    m_bodies[index]["Torso"] = {10,10,10,15};
    m_bodies[index]["Left_Leg"] = {10,20,3,25};
    m_bodies[index]["Right_Leg"] = {17,20,3,25};
    m_bodies[index]["Weapon"] = {7,5,2,40};
    ++index;

    //combat attack left
    m_bodies[index]["Head"] = {12,5,5,5};
    m_bodies[index]["Torso"] = {10,10,10,15};
    m_bodies[index]["Left_Leg"] = {10,20,3,25};
    m_bodies[index]["Right_Leg"] = {17,20,3,25};
    m_bodies[index]["Weapon"] = {7,17,40,2};
    ++index;

    //combat right
    m_bodies[index]["Head"] = {32,5,5,5};
    m_bodies[index]["Torso"] = {30,10,10,15};
    m_bodies[index]["Left_Leg"] = {30,20,3,25};
    m_bodies[index]["Right_Leg"] = {37,20,3,25};
    m_bodies[index]["Weapon"] = {41,5,2,40};
    ++index;

    //combat attack right
    m_bodies[index]["Head"] = {32,5,5,5};
    m_bodies[index]["Torso"] = {30,10,10,15};
    m_bodies[index]["Left_Leg"] = {30,20,3,25};
    m_bodies[index]["Right_Leg"] = {37,20,3,25};
    m_bodies[index]["Weapon"] = {7,14,40,2};
}

Army::~Army()
{

}

void Army::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_p: m_current_body_index = std::min(m_current_body_index+1, (signed)m_bodies.size()); break;
            case SDLK_o: m_current_body_index = std::max(m_current_body_index-1, 0); break;
        }
    }

    {
        int mouse_x = event.motion.x;
        int mouse_y = event.motion.y;

        m_mouse_hover = false;
        SDL_Rect auxilia = m_box_collider;
        auxilia.x += m_offset_x + m_origin_correction_x;
        auxilia.y += m_offset_y + m_origin_correction_y;

        if(PointInsideRect(auxilia, mouse_x, mouse_y))
        {
            m_mouse_hover = true;
        }
    }

    {
        if(m_mouse_hover && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && MouseClickCallBack != nullptr)
        {
            MouseClickCallBack();
            m_selected = true;
        }
    }
}

void Army::Logic(float fixed_frame_time)
{
    m_transform.UpdateSDLRects();
    m_offset_x = m_transform.GetGlobalSDLRect().x;
    m_offset_y = m_transform.GetGlobalSDLRect().y;
}

void Army::Render(SDL_Renderer *renderer, float delta_time, float scale)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect auxilia_rect{m_bodies[m_current_body_index]["Head"]};
    auxilia_rect.x += m_offset_x;
    auxilia_rect.y += m_offset_y;
    SDL_RenderFillRect(renderer, &auxilia_rect);

    auxilia_rect = m_bodies[m_current_body_index]["Left_Leg"];
    auxilia_rect.x += m_offset_x;
    auxilia_rect.y += m_offset_y;
    SDL_RenderFillRect(renderer, &auxilia_rect);

    auxilia_rect = m_bodies[m_current_body_index]["Weapon"];
    auxilia_rect.x += m_offset_x;
    auxilia_rect.y += m_offset_y;
    SDL_RenderFillRect(renderer, &auxilia_rect);

    SDL_SetRenderDrawColor(renderer, 255, 127, 127, 255);
    auxilia_rect = m_bodies[m_current_body_index]["Right_Leg"];
    auxilia_rect.x += m_offset_x;
    auxilia_rect.y += m_offset_y;
    SDL_RenderFillRect(renderer, &auxilia_rect);

    SDL_SetRenderDrawColor(renderer, 255, 0, 127, 255);
    auxilia_rect = m_bodies[m_current_body_index]["Torso"];
    auxilia_rect.x += m_offset_x;
    auxilia_rect.y += m_offset_y;
    SDL_RenderFillRect(renderer, &auxilia_rect);

    if(m_mouse_hover)
    {
        auxilia_rect = m_box_collider;
        auxilia_rect.x += m_offset_x;
        auxilia_rect.y += m_offset_y;
        SDL_RenderDrawRect(renderer, &auxilia_rect);
    }
}

void Army::CorrectOriginPosition(float x_correction, float y_correction)
{
    m_origin_correction_x = x_correction;
    m_origin_correction_y = y_correction;
}
