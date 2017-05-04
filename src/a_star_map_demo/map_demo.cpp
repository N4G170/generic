#include "map_demo.hpp"
#include "constants.hpp"
#include <functional>
#include "utils.hpp"
#include "message_writer.hpp"

MapDemo::MapDemo(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, TTF_Font* font):StateInterface(state_machine, state_name), m_mouse_inside_viewport{false},
m_map_width{0}, m_map_height{0}, m_scale{1}, m_mouse_hover_cell_index{-1}, m_selected_cell_index{-1}, m_army_selected{false}
{
    m_infobox.Config(nullptr, window_width - 275, 50, 250, 350);
    m_infobox.SetBgColour();

    int x{10}; int y{5}; int base_spacing{15};
    m_infobox.CreateLabel(LabelsId::BR1, renderer, font, x, y, "-------------------------", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::TITLE, renderer, font, x, y, "A* Map", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::MOUSE_POSITION, renderer, font, x, y, "Mouse", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::CURRENT_CELL, renderer, font, x, y, "Cell: -1 - (-1,-1)", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::L2, renderer, font, x, y, "L2", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::L3, renderer, font, x, y, "L3", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::L4, renderer, font, x, y, "L4", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::BR2, renderer, font, x, y, "-------------------------", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::SELECTED_CELL, renderer, font, x, y, "No Cell selected", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::ARMY, renderer, font, x, y, "No Army Selected", Colour::Black);
    y += 100;
    m_infobox.CreateLabel(LabelsId::BR3, renderer, font, x, y, "-------------------------", Colour::Black);
    y += base_spacing;
    m_infobox.CreateLabel(LabelsId::BACK, renderer, font, x, y, "'ESC' - Back to menu", Colour::Black);

    m_inner_box_viewport.Position(51, 51);
    m_inner_box_viewport.Width(1399);
    m_inner_box_viewport.Height(899);
    m_origin.Position(0, 0);
    //m_origin.SetParent(&m_inner_box_viewport);

    std::vector<unsigned char> map{
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 7, 5, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 2, 6, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 5, 5, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 3, 4, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 3, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 3, 3, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 3, 3, 3, 3, 3, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 1, 1, 1, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5,
        5, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 3, 3, 4, 3, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 4, 3, 4, 4, 3, 4, 4, 4, 4, 4, 3, 3, 3, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 3, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 4, 5,
        5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
        };

    m_cell_width = m_cell_height = 50;
    m_map_width_cell_count = 50;
    m_map_height_cell_count = 30;

    for(unsigned int i{0}; i < map.size(); ++i)
    {
        //We need to send the viewport to correct some offset error because SDL_RenderSetViewport uses its own origin instead of the one from the window
        //it also messes with mouse position readings
        Cell cell{map[i], static_cast<int>(i), static_cast<int>((i%m_map_width_cell_count)*m_cell_width), static_cast<int>((i/m_map_width_cell_count)*m_cell_height), m_cell_width, m_cell_height, &m_origin, &m_inner_box_viewport};
        cell.MouseHoverCallBack = std::bind(&MapDemo::CellMouseHover, this, std::placeholders::_1);
        cell.MouseClickCallBack = std::bind(&MapDemo::CellMouseClick, this, std::placeholders::_1);
        m_map.push_back(cell);
    }

    m_map_width = m_cell_width * 50;
    m_map_height = m_cell_height * 30;

    //armies
    m_player_army.TransformPtr()->SetParent(m_map[359].TransformPtr());
    m_player_army.CorrectOriginPosition(m_inner_box_viewport.PositionX(), m_inner_box_viewport.PositionY());
    m_player_army.MouseClickCallBack = std::bind(&MapDemo::ArmyMouseClick, this);
}

MapDemo::~MapDemo()
{

}

void MapDemo::Input(const SDL_Event& event)
{
    int mouse_x = event.motion.x;
    int mouse_y = event.motion.y;
    m_mouse_inside_viewport = PointInsideRect(m_inner_box_viewport.GetSDLRect(), mouse_x, mouse_y);
    m_infobox.ChangeText(LabelsId::MOUSE_POSITION, "Mouse: ("+std::to_string(mouse_x)+", "+std::to_string(mouse_y)+")");

    if(m_mouse_inside_viewport)
    {
        for(auto& cell : m_map)
            cell.Input(event);

        m_player_army.Input(event);
    }
    else
    {
        if(m_mouse_hover_cell_index >= 0)
        {
            m_mouse_hover_cell_index = -1;
            m_infobox.ChangeText(LabelsId::CURRENT_CELL,"Cell: -1 - (-1,-1)");

            for(auto& cell : m_map)
                cell.MouseOutsideViewport();
        }
    }

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
            case SDLK_KP_PLUS: m_scale+=0.1; break;
            case SDLK_KP_MINUS: m_scale-=0.1; break;
            case SDLK_KP_0: m_scale = 1; break;
        }
    }
    else if(event.type == SDL_MOUSEWHEEL)
    {
        if(event.wheel.y > 0)
            m_scale+=0.1;
        else
            m_scale-=0.1;
    }
    else if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button == SDL_BUTTON_MIDDLE || event.button.button == SDL_BUTTON_LEFT)
        {
            mid = true;
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP)
    {
        if(event.button.button == SDL_BUTTON_MIDDLE || event.button.button == SDL_BUTTON_LEFT)
        {
            mid = false;
        }
    }
    else if(mid && event.type == SDL_MOUSEMOTION)
    {
        //m_labels[1]->SetString("("+std::to_string(x)+", "+std::to_string(y)+") - "+std::to_string(m_map_width * m_scale) + " - " + std::to_string(m_map_height * m_scale));
        //m_infobox.ChangeText(LabelsId::L2, "("+std::to_string(m_inner_box_viewport.Width())+", "+std::to_string(m_map_height)+") - "+std::to_string(m_inner_box_viewport.Width() - m_map_width * m_scale));
        if(m_origin.PositionX() + event.motion.xrel > 0)
            m_origin.PositionX(0);
        else if(m_origin.PositionX() + m_map_width * m_scale + event.motion.xrel < m_inner_box_viewport.Width())
            m_origin.PositionX(m_inner_box_viewport.Width() - m_map_width * m_scale);
        else
            m_origin.PositionX(m_origin.PositionX() + event.motion.xrel);

        if(m_origin.Position().Y() + event.motion.yrel > 0)
            m_origin.PositionY(0);
        else if(m_origin.Position().Y() + m_map_height * m_scale + event.motion.yrel < m_inner_box_viewport.Height())
            m_origin.PositionY(m_inner_box_viewport.Height()- m_map_height * m_scale);
        else
            m_origin.PositionY(m_origin.PositionY() + event.motion.yrel);
    }
}

void MapDemo::Logic(float fixed_frame_time)
{
    m_player_army.Logic(fixed_frame_time);
}

void MapDemo::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_RenderSetViewport(renderer, m_inner_box_viewport.GetSDLRectPtr());
    SDL_RenderSetScale(renderer, m_scale, m_scale);
    for(unsigned int i{0}; i < m_map.size(); ++i)
    {
        m_map[i].Render(renderer, delta_time,m_scale);
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX(), m_origin.PositionX());
    SDL_RenderDrawPoint(renderer, m_origin.PositionX(), m_origin.PositionY()+1);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()+1, m_origin.PositionY());
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()+1, m_origin.PositionY()+1);

    SDL_RenderDrawPoint(renderer, m_origin.PositionX() + m_map_height * m_scale, m_origin.PositionX());
    SDL_RenderDrawPoint(renderer, m_origin.PositionX() + m_map_height * m_scale, m_origin.PositionY()+1);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()-1 + m_map_height * m_scale, m_origin.PositionY());
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()-1 + m_map_height * m_scale, m_origin.PositionY()+1);

    SDL_RenderDrawPoint(renderer, m_origin.PositionX(), m_origin.PositionX() + m_map_height * m_scale);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX(), m_origin.PositionY()-1 + m_map_height * m_scale);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()+1, m_origin.PositionY() + m_map_height * m_scale);
    SDL_RenderDrawPoint(renderer, m_origin.PositionX()+1, m_origin.PositionY()-1 + m_map_height * m_scale);

    //armies
    m_player_army.Render(renderer, delta_time, m_scale);

    SDL_RenderSetViewport(renderer, 0);
    SDL_RenderSetScale(renderer, 1, 1);

    m_infobox.Render(renderer, delta_time);

    //render bounding box
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer,  &m_outter_box);
    SDL_RenderDrawRect(renderer,  &m_inner_box);

    int mouse_x = 0;
    int mouse_y = 0;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect r{mouse_x, mouse_y,2,2};
    SDL_RenderFillRect(renderer, &r);

}

//<f> CallBacks
void MapDemo::CellMouseHover(int cell_index)
{
    if(m_mouse_hover_cell_index != cell_index)
    {
        m_mouse_hover_cell_index = cell_index;
        m_infobox.ChangeText(LabelsId::CURRENT_CELL, "Cell: "+std::to_string(m_mouse_hover_cell_index)+" - ("+ std::to_string((int)(m_mouse_hover_cell_index % m_map_width_cell_count))
                            +","+ std::to_string((int)(m_mouse_hover_cell_index / m_map_height_cell_count)) +")");
    }
}

void MapDemo::CellMouseClick(int cell_index)
{
    if(m_selected_cell_index != cell_index)
    {
        if(m_selected_cell_index > -1)
            m_map[m_selected_cell_index].Deselect();
        m_selected_cell_index = cell_index;
        m_infobox.ChangeText(LabelsId::SELECTED_CELL, "Selected Cell: "+std::to_string(m_mouse_hover_cell_index)+" - ("+ std::to_string((int)(m_mouse_hover_cell_index % m_map_width_cell_count))
                            +","+ std::to_string((int)(m_mouse_hover_cell_index / m_map_height_cell_count)) +")");
    }
}

// void MapDemo::ArmyMouseHover(bool hover)
// {
//     if(m_ar != cell_index)
//     {
//         m_mouse_hover_cell_index = cell_index;
//         m_infobox.ChangeText(LabelsId::CURRENT_CELL, "Cell: "+std::to_string(m_mouse_hover_cell_index)+" - ("+ std::to_string((int)(m_mouse_hover_cell_index % m_map_width_cell_count))
//                             +","+ std::to_string((int)(m_mouse_hover_cell_index / m_map_height_cell_count)) +")");
//     }
// }

void MapDemo::ArmyMouseClick()
{
    m_army_selected = true;
    m_infobox.ChangeText(LabelsId::ARMY, "Selected Army: TRUE");

}
//</f>
