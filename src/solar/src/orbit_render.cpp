#include "orbit_render.hpp"
#include <utility>
#include "vector3_utils.hpp"
#include "utils.hpp"
#include "debug_render.hpp"

//<f> Constructors & operator=
OrbitRender::OrbitRender(SystemManager* system_manager): RenderScript{}, m_system_manager{system_manager},
    m_texture{system_manager->Renderer(), Vector3<float>{1,1,0}}, //texture size cannot be 0
    m_orbit_colour{255,255,255,255}
{
}

OrbitRender::~OrbitRender() noexcept
{

}

OrbitRender::OrbitRender(const OrbitRender& other): RenderScript{other}, m_system_manager{other.m_system_manager}, m_texture{other.m_texture}, m_orbit_colour{other.m_orbit_colour}
{

}

OrbitRender::OrbitRender(OrbitRender&& other) noexcept: RenderScript{std::move(other)}, m_system_manager{std::move(other.m_system_manager)}, m_texture{std::move(other.m_texture)},
    m_orbit_colour{std::move(other.m_orbit_colour)}
{

}

OrbitRender& OrbitRender::operator=(const OrbitRender& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

OrbitRender& OrbitRender::operator=(OrbitRender&& other) noexcept
{
    if(this != &other)//not same ref
    {
         m_system_manager = std::move(other.m_system_manager);
         m_texture = std::move(other.m_texture);
         m_orbit_colour = std::move(other.m_orbit_colour);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* OrbitRender::Clone() { return new OrbitRender{*this}; }

void OrbitRender::Render(float delta_time)
{
    auto camera{m_system_manager->MainCamera()};

    if(m_owner == nullptr)
        return;

    auto position{m_owner->TransformPtr()->GlobalPosition()};
    auto size{m_owner->TransformPtr()->GlobalScale()};//we use the scale as the size
    position = AjustPositionToAnchor(position, size, m_owner->TransformPtr()->Anchor());

    position += m_position_offset;

    auto rotation{m_owner->TransformPtr()->GlobalRotation().Z()};
    SDL_Rect dst{RectFromFloats(position.X(), position.Y(), std::abs(size.X()), std::abs(size.Y()))};

    int flip{SDL_FLIP_NONE};

    if(size.X() < 0)
        flip |= SDL_FLIP_HORIZONTAL;
    if(size.Y() < 0)
        flip |= SDL_FLIP_VERTICAL;

    //check if inside camera
    auto bounds{m_owner->TransformPtr()->LocalBounds()};

    if(camera->InsideCamera(bounds))
    {
        camera->SetAsTarget();
        m_texture.RenderEx(nullptr, &dst, rotation, nullptr, static_cast<SDL_RendererFlip>(flip));
        camera->RemoveAsTarget();
    }

    // DebugRender::Instance()->RenderDrawPoint(m_position_offset + position, {255,0,0,255});
}
//</f> /Virtual Methods

//<f> Getters/Setters
void OrbitRender::OrbitColour(const SDL_Colour& orbit_colour) { m_orbit_colour = orbit_colour; }
SDL_Colour OrbitRender::OrbitColour() const { return m_orbit_colour; }

void OrbitRender::RotationAngle(float angle)
{
    if(m_owner == nullptr)
        return;
    m_owner->TransformPtr()->GlobalRotationZ(angle);
}

void OrbitRender::PositionOffset(const Vector3<float>& position_offset){ m_position_offset = position_offset; }
//</f> /Getters/Setters

//<f> Methods
void OrbitRender::RebuildOrbit(float perihelion, float aphelion, const std::vector<Vector3<float>>& points)
{
    if(m_owner == nullptr)
        return;

    m_owner->TransformPtr()->GlobalScale({aphelion * 2, perihelion * 2, 1});//cannot use local scale was we have a parent and it is scaled
    m_owner->TransformPtr()->Anchor(AnchorType::Centre_Centre);

    m_texture.Resize(CoordinateToInt(aphelion * 2) + 1, CoordinateToInt(perihelion * 2) + 1);
    m_texture.Clear();

    for(auto point : points)
    {
        point += {aphelion, perihelion,0};
        m_texture.RenderDrawPointOnSelf(point, m_orbit_colour);
    }
}
//</f> /Methods
