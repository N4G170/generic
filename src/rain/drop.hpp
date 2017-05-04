#ifndef DROP_HPP
#define DROP_HPP

#include <SDL2/SDL.h>
#include <functional>

#include "object.hpp"

class  Drop : public Object
{
    public:
        explicit Drop(const std::function<void()>&);
        void Logic(float delta_time = 1);
        void Render(SDL_Renderer* renderer, float delta_time);

    private:
        SDL_Colour m_colour;

        SDL_Rect m_splash;
        float m_splash_time;
        bool m_show_splash;

        void NewStartPosition();
        float m_velocity;
        int m_z_index;

        std::function<void()> m_drop_sound;
};
#endif //DROP_HPP
