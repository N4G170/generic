#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>
#include "vector2.hpp"
#include "SDL2/SDL.h"

class Transform
{
    public:
        Transform();
        ~Transform();

        void SetParent(Transform*);
        void RemoveChild(Transform*);
        void UpdateSDLRects();

//<f> Getters & Setters
        void Position(const Vector2<float>& position){ m_position = position; UpdateSDLRects(); }
        void Position(const float& x, const float& y){ m_position.X(x); m_position.Y(y); UpdateSDLRects(); }
        void PositionX(const float& x){ m_position.X(x); UpdateSDLRects(); }
        void PositionY(const float& y){ m_position.Y(y); UpdateSDLRects(); }
        float PositionX() const { return m_position.X(); }
        float PositionY() const { return m_position.Y(); }
        /**
         * \return This function returns by value
         */
        Vector2<float> Position() const { return m_position; }

        Vector2<float> GlobalPosition();

        void Width(const int& width){ m_width = width; UpdateSDLRects(); }
        const int Width() const { return m_width; }
        void Height(const int& height){ m_height = height; UpdateSDLRects(); }
        const int Height() const { return m_height; }

        void Scale(const int& scale){ m_scale = scale; }
        const int Scale() const { return m_scale; }

        SDL_Rect GetSDLRect() const { return m_sdl_rect; }
        SDL_Rect* GetSDLRectPtr() { return &m_sdl_rect; }
        SDL_Rect GetGlobalSDLRect() const { return m_global_sdl_rect; }
        SDL_Rect* GetGlobalSDLRectPtr() { return &m_global_sdl_rect; }
//</f>

    private:
        Vector2<float> m_position;
        int m_width;
        int m_height;
        float m_scale;

        SDL_Rect m_sdl_rect;
        SDL_Rect m_global_sdl_rect;

        Transform* m_parent;
        std::vector<Transform*> m_children;
};

#endif //TRANSFORM_HPP
