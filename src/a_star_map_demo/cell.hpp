#ifndef CELL_HPP
#define CELL_HPP

#include <functional>
#include "object.hpp"


class Cell:public Object
{
    public:
        Cell();
        Cell(unsigned char type, int grid_index, int x, int y, int width, int height, Transform* parent, Transform* viewport);
        virtual ~Cell();
        void Type(const unsigned char& type){ m_type = type; }
        unsigned char Type() const {return m_type; }

        void ConfigCell(unsigned char type, int grid_index, int x, int y, int width, int height, Transform* parent, Transform* viewport);
        void Input(const SDL_Event& event);
        void Logic(float fixed_frame_time);
        void Render(SDL_Renderer *renderer, float delta_time, float scale);

        void MouseOutsideViewport();
        void Deselect();

        std::function<void(int)> MouseHoverCallBack;
        std::function<void(int)> MouseClickCallBack;
    private:
        unsigned char m_type;
        int m_grid_index;
        SDL_Colour m_colour;
        bool m_mouse_hover;
        bool m_selected;

        //We need to send the viewport to correct some offset error because SDL_RenderSetViewport uses its own origin instead of the one from the window
        Transform* m_viewport;
};

#endif //CELL_HPP
