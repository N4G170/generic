#include "cell.hpp"
#include "utils.hpp"

Cell::Cell():Object(), m_type{0}, m_grid_index{0}, m_mouse_hover{false}, m_selected{false}, m_viewport{nullptr}
{

}
//We need to send the viewport to correct some offset error because SDL_RenderSetViewport uses its own origin instead of the one from the window
Cell::Cell(unsigned char type, int grid_index, int x, int y, int width, int height, Transform* parent, Transform* viewport):Object(), m_type{0}, m_mouse_hover{false}
{
    ConfigCell(type, grid_index, x, y, width, height, parent, viewport);
}

Cell::~Cell()
{

}

void Cell::ConfigCell(unsigned char type, int grid_index, int x, int y, int width, int height, Transform* parent, Transform* viewport)
{
    m_type = type;
    m_colour.a = 255;
    m_grid_index = grid_index;

    m_viewport = viewport;

    switch(m_type)
    {
        case 1: m_colour.r = 38, m_colour.g = 127, m_colour.b = 0; break;//dark green
        case 2: m_colour.r = 127, m_colour.g = 51, m_colour.b = 0; break;//brown
        case 3: m_colour.r = 0, m_colour.g = 127, m_colour.b = 127; break;//lighter blue
        case 4: m_colour.r = 0, m_colour.g = 74, m_colour.b = 127; break;//darker blue
        case 5: m_colour.r = 64, m_colour.g = 64, m_colour.b = 64; break;//grey
        case 6: m_colour.r = 255, m_colour.g = 0, m_colour.b = 0; break;//red
        case 7: m_colour.r = 76, m_colour.g = 255, m_colour.b = 0; break;//light green
    }

    m_transform.SetParent(parent);
    m_transform.Position(x, y);
    m_transform.Width(width);
    m_transform.Height(height);
}

void Cell::Input(const SDL_Event& event)
{
    bool prev_hover {m_mouse_hover};

    //if(event.type == SDL_MOUSEMOTION)
    {
        SDL_Rect cell = m_transform.GetGlobalSDLRect();
        //correct position because of viewport
        cell.x += m_viewport->PositionX();
        cell.y += m_viewport->PositionY();

        int mouse_x = event.motion.x;
        int mouse_y = event.motion.y;

        //bool previous_status = m_mouse_hover;
        m_mouse_hover = false;

        if(PointInsideRect(cell, mouse_x, mouse_y))
        {
            m_mouse_hover = true;
        }
    }

    if(m_mouse_hover && prev_hover != m_mouse_hover && MouseHoverCallBack != nullptr)
        MouseHoverCallBack(m_grid_index);
    if(m_mouse_hover && event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && MouseClickCallBack != nullptr)
    {
        MouseClickCallBack(m_grid_index);
        m_selected = true;
    }
}

void Cell::Logic(float fixed_frame_time)
{

}

void Cell::Render(SDL_Renderer *renderer, float delta_time, float scale)
{
    m_transform.UpdateSDLRects();

    SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
    SDL_RenderFillRect(renderer, m_transform.GetGlobalSDLRectPtr());

    if(m_selected)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 127);
        SDL_RenderFillRect(renderer, m_transform.GetGlobalSDLRectPtr());
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

        //centre
        SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
        SDL_Rect rect = *m_transform.GetGlobalSDLRectPtr();
        rect.x += 5;
        rect.y += 5;
        rect.w -= 10;
        rect.h -= 10;
        SDL_RenderFillRect(renderer, &rect);
    }
    if(m_mouse_hover)
    {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
        SDL_RenderDrawRect(renderer, m_transform.GetGlobalSDLRectPtr());
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    }

}

void Cell::MouseOutsideViewport()
{
    m_mouse_hover = false;
}

void Cell::Deselect()
{
    m_selected = false;
}
