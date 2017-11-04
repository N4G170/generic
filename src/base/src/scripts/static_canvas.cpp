#include "static_canvas.hpp"
#include <utility>
#include "utils.hpp"

//<f> Constructors & operator=
StaticCanvas::StaticCanvas(SystemManager* system_manager): RenderScript{}, m_system_manager{system_manager}, m_texture{system_manager->Renderer(), 1, 1}
{
    m_texture.Clear({255,255,255,0});
}

StaticCanvas::~StaticCanvas() noexcept
{

}

StaticCanvas::StaticCanvas(const StaticCanvas& other)
{

}

StaticCanvas::StaticCanvas(StaticCanvas&& other) noexcept
{

}

StaticCanvas& StaticCanvas::operator=(const StaticCanvas& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

StaticCanvas& StaticCanvas::operator=(StaticCanvas&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* StaticCanvas::Clone() { return new StaticCanvas{*this}; }
void StaticCanvas::Render(float delta_time)
{
    if(m_owner == nullptr)
        return;

    auto camera = m_system_manager->MainCamera();

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
    auto bounds{m_owner->TransformPtr()->LocalBounds(camera)};
    if(camera->InsideCamera(bounds))
    {
        camera->SetAsTarget();
        m_texture.RenderEx(nullptr, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
        camera->RemoveAsTarget();
    }
}
//</f> /Virtual Methods

//<f> Content Mangement
void StaticCanvas::AddImage(const std::string& path, SDL_Rect* src, SDL_Rect* dst, SDL_Colour colour, double angle, SDL_Point *rotation_pivot, SDL_RendererFlip flip)
{
    //load image
    auto texture = m_system_manager->Resources()->GetTexture(path);

    //render image on canvas
    SetAsTarget();
    texture.ColourModulation(colour);
    texture.RenderEx(src, dst, angle, rotation_pivot, flip);
    RemoveAsTarget();
}

void StaticCanvas::AddImage(Image* source_image)
{
    //render image on canvas
    SetAsTarget();
    source_image->RenderToMask(1);
    RemoveAsTarget();
}

void StaticCanvas::SetAsTarget()
{
    SDL_SetRenderTarget(m_system_manager->Renderer(), m_texture.TexturePtr());
}

void StaticCanvas::RemoveAsTarget()
{
    SDL_SetRenderTarget(m_system_manager->Renderer(), nullptr);
}
//</f> /Content Mangement

//<f> Getters/Setters
Vector3<float> StaticCanvas::CanvasSize() const
{
    return m_canvas_size;
}

void StaticCanvas::CanvasSize(const Vector3<float>& size)
{
    m_canvas_size = size;
    m_texture.Resize(CoordinateToInt(size.X()), CoordinateToInt(size.Y()));
}
//</f> /Getters/Setters
