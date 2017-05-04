#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SDL2/SDL.h>
#include "transform.hpp"
#include <functional>

class Object
{
    public:
        //TODO: move to transform???
        const SDL_Rect DimensionsRect() const{ return { static_cast<int>(m_transform.Position().X()), static_cast<int>(m_transform.Position().Y()), m_transform.Width(), m_transform.Height() }; }
        //Transform GetTransform() const { return m_transform; }
        Transform* TransformPtr() { return &m_transform; }

    protected:
        Transform m_transform;
};

#endif //OBJECT_HPP
