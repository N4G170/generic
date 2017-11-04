#include "image.hpp"
#include <utility>
#include "constants.hpp"
#include "object.hpp"
#include "utils.hpp"
#include <iostream>

//<f> Constructors & operator=
Image::Image(SystemManager* system_manager): RenderScript{}, m_resource_manager{system_manager->Resources()}, m_camera{system_manager->MainCamera()}, m_texture{},
    m_has_src_rect{false}, m_src_rect{0,0,1,1}
{
    m_texture = m_resource_manager->GetTexture(c_white_dot);
}

Image::~Image() noexcept
{

}

Image::Image(const Image& other): RenderScript{other}, m_resource_manager{other.m_resource_manager}, m_camera{other.m_camera}, m_texture{other.m_texture},
    m_has_src_rect{other.m_has_src_rect}, m_src_rect{other.m_src_rect}
{

}

Image::Image(Image&& other) noexcept: RenderScript{std::move(other)}, m_resource_manager{std::move(other.m_resource_manager)}, m_camera{std::move(other.m_camera)},
    m_texture{std::move(other.m_texture)}, m_has_src_rect{std::move(other.m_has_src_rect)}, m_src_rect{std::move(other.m_src_rect)}
{

}

Image& Image::operator=(const Image& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Image& Image::operator=(Image&& other) noexcept
{
    if(this != &other)//not same ref
    {
        RenderScript::operator=(std::move(other));
        m_resource_manager = std::move(other.m_resource_manager);
        m_camera = std::move(other.m_camera);
        m_texture = std::move(other.m_texture);
        m_has_src_rect = std::move(other.m_has_src_rect);
        m_src_rect = std::move(other.m_src_rect);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Image::Clone() { return new Image{*this}; }

void Image::Render(float delta_time)
{
    if(m_owner == nullptr)
        return;
    if(m_camera == nullptr)
        return;

    auto position{m_owner->TransformPtr()->GlobalPosition()};
    auto size{m_owner->TransformPtr()->GlobalScale()};//we use the scale as the size
    position = AjustPositionToAnchor(position, size, m_owner->TransformPtr()->Anchor());

    auto rotation{m_owner->TransformPtr()->GlobalRotation().Z()};
    SDL_Rect dst{RectFromFloats(position.X(), position.Y(), std::abs(size.X()), std::abs(size.Y()))};

    int flip{SDL_FLIP_NONE};

    if(size.X() < 0)
        flip |= SDL_FLIP_HORIZONTAL;
    if(size.Y() < 0)
        flip |= SDL_FLIP_VERTICAL;

    //check if inside camera
    auto bounds{m_owner->TransformPtr()->LocalBounds(m_camera)};
    if(m_camera->InsideCamera(bounds))
    {
        m_camera->SetAsTarget();
        if(m_has_src_rect)
            m_texture.RenderEx(&m_src_rect, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
        else
            m_texture.RenderEx(nullptr, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
        m_camera->RemoveAsTarget();
    }
}
//</f> /Virtual Methods

//<f> Methods
void Image::RenderToMask(float delta_time)
{
    if(m_owner == nullptr)
        return;
    if(m_camera == nullptr)
        return;

    auto position{m_owner->TransformPtr()->GlobalPosition()};
    auto size{m_owner->TransformPtr()->GlobalScale()};//we use the scale as the size
    position = AjustPositionToAnchor(position, size, m_owner->TransformPtr()->Anchor());

    auto rotation{m_owner->TransformPtr()->GlobalRotation().Z()};
    SDL_Rect dst{RectFromFloats(position.X(), position.Y(), std::abs(size.X()), std::abs(size.Y()))};

    int flip{SDL_FLIP_NONE};

    if(size.X() < 0)
        flip |= SDL_FLIP_HORIZONTAL;
    if(size.Y() < 0)
        flip |= SDL_FLIP_VERTICAL;

    if(m_has_src_rect)
        m_texture.RenderEx(&m_src_rect, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
    else
        m_texture.RenderEx(nullptr, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
}
//</f> /Methods

//<f> Getters/Setters
void Image::SetImage(const std::string& path)
{
    if(m_resource_manager != nullptr)
        m_texture = m_resource_manager->GetTexture(path);
    m_has_src_rect = false;
}

Texture* Image::GetTexture() { return &m_texture; }

void Image::ColourModulation(const SDL_Colour& colour) { m_texture.ColourModulation(colour); };
SDL_Colour Image::ColourModulation() const { return m_texture.ColourModulation(); };

bool Image::HasSrcRect() const { return m_has_src_rect; }
void Image::HasSrcRect(bool has_src_rect) { m_has_src_rect = has_src_rect; }

SDL_Rect Image::SrcRect() const { return m_src_rect; }
void Image::SrcRect(const SDL_Rect& src_rect) { m_src_rect = src_rect; }
//</f> /Getters/Setters
