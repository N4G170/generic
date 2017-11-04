#include "camera.hpp"
#include <utility>
#include "constants.hpp"
#include "vector3_utils.hpp"
#include "debug_render.hpp"
#include "utils.hpp"

//<f> Constructors & operator=
Camera::Camera(SDL_Renderer* renderer): m_position{0,0,-10}, m_renderer{renderer}, m_size{window_width, window_height, 1000},
    m_texture{ renderer, window_width, window_height }, m_clear_colour{0,0,0,255}
{

}

Camera::~Camera() noexcept
{

}

Camera::Camera(const Camera& other) : m_position{other.m_position}, m_renderer{other.m_renderer}, m_size{other.m_size},
    m_texture{ other.m_texture }
{

}

Camera::Camera(Camera&& other) noexcept: m_position{std::move(other.m_position)}, m_renderer{std::move(other.m_renderer)}, m_size{std::move(other.m_size)},
    m_texture{ std::move(other.m_texture) }
{

}

Camera& Camera::operator=(const Camera& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Camera& Camera::operator=(Camera&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_position = std::move(other.m_position);
        m_renderer = std::move(other.m_renderer);
        m_size = std::move(other.m_size);
        m_texture = std::move(other.m_texture);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Camera::Clone() { return new Camera{*this}; }
//</f> /Virtual Methods

//<f> Getters/Setters
Vector3<float> Camera::Size() const { return m_size; }
void Camera::Size(const Vector3<float>& size) { if(m_size != size) { m_size = size; ResizeTexture(); } }

float Camera::CameraWidth() const { return m_size.X(); }
void Camera::CameraWidth(float width) { if(m_size.X() != width) { m_size.X(width); ResizeTexture(); } }

float Camera::CameraHeight() const { return m_size.Y(); }
void Camera::CameraHeight(float height) { if(m_size.Y() != height) { m_size.Y(height); ResizeTexture(); } }

float Camera::CameraDepth() const { return m_size.Z(); }
void Camera::CameraDepth(float depth) { m_size.Z(depth); }
//</f> /Getters/Setters

//<f> Render Control
void Camera::Render(float delta_time)
{
    SDL_Rect dst{Vectors3ToSDLRect({0,0,-10}, m_size)};
    m_texture.Render(nullptr, &dst);
}
/**
 * \brief Clears the content from the internal texture
 */
void Camera::ClearCamera()
{
    SetAsTarget();
    SDL_SetRenderDrawColor(m_renderer, m_clear_colour.r, m_clear_colour.g, m_clear_colour.b, m_clear_colour.a);
    SDL_RenderClear(m_renderer);
    RemoveAsTarget();
}
/**
 * \brief Set the internal camera texture as render target
 */
void Camera::SetAsTarget() { SDL_SetRenderTarget(m_renderer, m_texture.TexturePtr()); }
/**
 * \brief Remove the internal camera texture as render target
 */
void Camera::RemoveAsTarget() { SDL_SetRenderTarget(m_renderer, nullptr);}

void Camera::StartRenderMask()
{
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BlendMode::SDL_BLENDMODE_MOD);
    SDL_SetTextureBlendMode(m_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_MOD);
}

void Camera::StopRenderMask()
{
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BlendMode::SDL_BLENDMODE_NONE);
    SDL_SetTextureBlendMode(m_texture.TexturePtr(), SDL_BlendMode::SDL_BLENDMODE_NONE);
}

Bounds<float> Camera::CameraBounds() const
{
    return { m_position, m_size };
}

bool Camera::InsideCamera(Bounds<float> element_bounds)
{
    Bounds<float> camera_bounds{ CameraBounds() };

    //add camera position
    // element_bounds.

    return BoundsCollision(camera_bounds, element_bounds);
}
//</f> /Render Control

//<f> Position Control
Vector3<float> Camera::ToWorldSpace(const Vector3<float>& position)
{
    //screen + camera
    return position + m_position;
}
Vector3<float> Camera::ToScreenSpace(const Vector3<float>& position)
{
    //world - camera
    return position - m_position;
}
//</f> /Position Control

//<f> Private Methods
void Camera::ResizeTexture()
{
    m_texture.Resize(CoordinateToInt(m_size.X()), CoordinateToInt(m_size.Y()));
}
//</f> /Private Methods
