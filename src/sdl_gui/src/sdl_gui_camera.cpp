#include "sdl_gui_camera.hpp"
#include <utility>

//<f> Constructors & operator=
Camera::Camera()
{
    
}

Camera::~Camera() noexcept
{

}

Camera::Camera(const Camera& other)
{

}

Camera::Camera(Camera&& other) noexcept
{

}

Camera& Camera::operator=(const Camera& other)
{
    if(this != &other)//not same ref
    {
        Camera tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Camera& Camera::operator=(Camera&& other) noexcept
{
    return *this;
}
//</f>
