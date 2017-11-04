#include "transform.hpp"
#include <algorithm>

//<f> Constructors & operator=
Transform::Transform(): m_instance_id{GenerateUID()}, m_local_position{0,0,0}, m_local_scale{1,1,1}, m_local_rotation{0,0,0}, m_owner{nullptr},
    m_parent{nullptr}, m_children{}, m_anchor_type{AnchorType::Centre_Centre} {}
Transform::~Transform() noexcept {}

Transform::Transform(const Transform& other): m_instance_id{GenerateUID()}, m_local_position{other.m_local_position}, m_local_scale{other.m_local_scale},
    m_local_rotation{other.m_local_rotation}, m_owner{other.m_owner}, m_parent{nullptr}, m_children{}, m_anchor_type{other.m_anchor_type}
{
    //we cannot copy the children as they can only have one parent
    Parent(other.m_parent);
}

Transform::Transform(Transform&& other) noexcept: m_instance_id{std::move(other.m_instance_id)}, m_local_position{std::move(other.m_local_position)},
    m_local_scale{std::move(other.m_local_scale)}, m_local_rotation{std::move(other.m_local_rotation)},
    m_owner{std::move(other.m_owner)}, m_parent{std::move(other.m_parent)}, m_children{std::move(other.m_children)},
    m_anchor_type{std::move(other.m_anchor_type)} {}

Transform& Transform::operator=(const Transform& other)
{
    if(this != &other)
    {
        auto tmp{other};
        *this = std::move(other);
    }
    return *this;
}
Transform& Transform::operator=(Transform&& other) noexcept
{
    if(this != &other)
    {
        m_instance_id = std::move(other.m_instance_id);
        m_local_position = std::move(other.m_local_position);
        m_local_scale = std::move(other.m_local_scale);
        m_local_rotation = std::move(other.m_local_rotation);
        m_owner = std::move(other.m_owner);
        m_parent = std::move(other.m_parent);
        m_children = std::move(other.m_children);
        m_anchor_type = std::move(other.m_anchor_type);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Position
//<f> LocalPosition
Vector3<float> Transform::LocalPosition() const { return m_local_position; }
void Transform::LocalPosition(const Vector3<float>& local_position) { m_local_position = local_position; }
void Transform::LocalPositionX(float local_position_x) { m_local_position.X(local_position_x); }
void Transform::LocalPositionY(float local_position_y) { m_local_position.Y(local_position_y); }
void Transform::LocalPositionZ(float local_position_z) { m_local_position.Z(local_position_z); }
//</f> /LocalPosition

//<f> GlobalPosition
Vector3<float> Transform::GlobalPosition() const
{
    auto global_position{m_local_position};

    if(m_parent != nullptr)
        global_position = m_local_position + m_parent->GlobalPosition();

    return global_position;
}
void Transform::GlobalPosition(const Vector3<float>& global_position)
{
    auto current_global_position{GlobalPosition()};//get current global position
    //calculate the new local position based con current and new globals
    m_local_position = m_local_position + global_position - current_global_position;
}
void Transform::GlobalPositionX(float global_position_x)
{
    auto current_global_position_x{GlobalPosition().X()};//get current global position
    //calculate the new local position based con current and new globals
    m_local_position.X( m_local_position.X() + global_position_x - current_global_position_x);
}
void Transform::GlobalPositionY(float global_position_y)
{
    auto current_global_position_y{GlobalPosition().Y()};//get current global position
    //calculate the new local position based con current and new globals
    m_local_position.Y( m_local_position.Y() + global_position_y - current_global_position_y);
}
void Transform::GlobalPositionZ(float global_position_z)
{
    auto current_global_position_z{GlobalPosition().Z()};//get current global position
    //calculate the new local position based con current and new globals
    m_local_position.Z( m_local_position.Z() + global_position_z - current_global_position_z);
}
//</f> /GlobalPosition
//</f> /Position

//<f> Scale/Size
//<f> LocalScale
Vector3<float> Transform::LocalScale() const { return m_local_scale; }
void Transform::LocalScale(const Vector3<float>& local_scale) { m_local_scale = local_scale; }
void Transform::LocalScaleX(float local_scale_x) { m_local_scale.X(local_scale_x); }
void Transform::LocalScaleY(float local_scale_y) { m_local_scale.Y(local_scale_y); }
void Transform::LocalScaleZ(float local_scale_z) { m_local_scale.Z(local_scale_z); }
//</f> /LocalScale

//<f> GlobalScale
Vector3<float> Transform::GlobalScale() const
{
    auto global_scale{m_local_scale};

    if(m_parent != nullptr)
        global_scale = m_local_scale * m_parent->GlobalScale();

    return global_scale;
}
void Transform::GlobalScale(const Vector3<float>& global_scale)
{
    auto current_global_scale{GlobalScale()};//get current global scale
    //calculate the new local scale based con current and new globals
    m_local_scale = global_scale / current_global_scale / m_local_scale;
}
void Transform::GlobalScaleX(float global_scale_x)
{
    auto current_global_scale_x{GlobalScale().X()};//get current global scale
    //calculate the new local scale based con current and new globals
    m_local_scale.X(global_scale_x / current_global_scale_x / m_local_scale.X());
}
void Transform::GlobalScaleY(float global_scale_y)
{
    auto current_global_scale_y{GlobalScale().Y()};//get current global scale
    //calculate the new local scale based con current and new globals
    m_local_scale.Y(global_scale_y / current_global_scale_y / m_local_scale.Y());
}
void Transform::GlobalScaleZ(float global_scale_z)
{
    auto current_global_scale_z{GlobalScale().Z()};//get current global scale
    //calculate the new local scale based con current and new globals
    m_local_scale.Z(global_scale_z / current_global_scale_z / m_local_scale.Z());
}
//</f> /GlobalScale

/**
 * \brief Returns Local bounds (uses local_position and local_scale)
 */
Bounds<float> Transform::LocalBounds()
{
    return {GlobalPosition(), m_local_scale};
}
/**
 * \brief Returns Local bounds (uses local_position and local_scale)
 */
Bounds<float> Transform::LocalBounds(Camera* camera)
{
    return {camera->ToScreenSpace(GlobalPosition()), m_local_scale};
}
/**
 * \brief Gets bounds from self and children and calculates global mins and maxs
 */
Bounds<float> Transform::GlobalBounds()
{
    auto bounds{LocalBounds()};

    for(auto& child : m_children)
    {
        auto child_bounds{child->GlobalBounds()};

        if(child_bounds.min_x < bounds.min_x)
            bounds.min_x = child_bounds.min_x;
        if(child_bounds.max_x > bounds.max_x)
            bounds.max_x = child_bounds.max_x;

        if(child_bounds.min_y < bounds.min_y)
            bounds.min_y = child_bounds.min_y;
        if(child_bounds.max_y > bounds.max_y)
            bounds.max_y = child_bounds.max_y;

        if(child_bounds.min_z < bounds.min_z)
            bounds.min_z = child_bounds.min_z;
        if(child_bounds.max_z > bounds.max_z)
            bounds.max_z = child_bounds.max_z;
    }

    return bounds;
}

Bounds<float> Transform::GlobalBounds(Camera* camera)
{
    auto bounds{LocalBounds(camera)};

    for(auto& child : m_children)
    {
        auto child_bounds{child->GlobalBounds(camera)};

        if(child_bounds.min_x < bounds.min_x)
            bounds.min_x = child_bounds.min_x;
        if(child_bounds.max_x > bounds.max_x)
            bounds.max_x = child_bounds.max_x;

        if(child_bounds.min_y < bounds.min_y)
            bounds.min_y = child_bounds.min_y;
        if(child_bounds.max_y > bounds.max_y)
            bounds.max_y = child_bounds.max_y;

        if(child_bounds.min_z < bounds.min_z)
            bounds.min_z = child_bounds.min_z;
        if(child_bounds.max_z > bounds.max_z)
            bounds.max_z = child_bounds.max_z;
    }

    return bounds;
}
//</f> /Scale/Size

//<f> Rotation
//<f> LocalRotation
Vector3<float> Transform::LocalRotation() const { return m_local_rotation; }
void Transform::LocalRotation(const Vector3<float>& local_rotation) { m_local_rotation = local_rotation; }
void Transform::LocalRotationX(float local_rotation_x) { m_local_rotation.X(local_rotation_x); }
void Transform::LocalRotationY(float local_rotation_y) { m_local_rotation.Y(local_rotation_y); }
void Transform::LocalRotationZ(float local_rotation_z) { m_local_rotation.Z(local_rotation_z); }
//</f> /LocalRotation

//<f> GlobalRotation
Vector3<float> Transform::GlobalRotation() const
{
    auto global_rotation{m_local_rotation};

    if(m_parent != nullptr)
        global_rotation = m_local_rotation + m_parent->GlobalRotation();

    return global_rotation;
}
void Transform::GlobalRotation(const Vector3<float>& global_rotation)
{
    auto current_global_rotation{GlobalRotation()};//get current global position
    //calculate the new local rotation based on current and new globals
    m_local_rotation = m_local_rotation + global_rotation - current_global_rotation;
}
void Transform::GlobalRotationX(float global_rotation_x)
{
    auto current_global_rotation_x{GlobalRotation().X()};//get current global position
    //calculate the new local rotation based on current and new globals
    m_local_rotation.X(m_local_rotation.X() + global_rotation_x - current_global_rotation_x);
}
void Transform::GlobalRotationY(float global_rotation_y)
{
    auto current_global_rotation_y{GlobalRotation().Y()};//get current global position
    //calculate the new local rotation based on current and new globals
    m_local_rotation.Y(m_local_rotation.Y() + global_rotation_y - current_global_rotation_y);
}
void Transform::GlobalRotationZ(float global_rotation_z)
{
    auto current_global_rotation_z{GlobalRotation().Z()};//get current global position
    //calculate the new local rotation based on current and new globals
    m_local_rotation.Z(m_local_rotation.Z() + global_rotation_z - current_global_rotation_z);
}
//</f> /GlobalRotation
//</f> /Rotation

//<f> Hierarchy (parents/children)
void Transform::Parent(Transform* parent)
{
    if(m_parent != nullptr)//already has parent
    {
        m_parent->RemoveChild(InstanceID());//use our id
    }

    m_parent = parent;
    if(m_parent != nullptr)//we assigned another parent (if nullptr we lose the parent)
        m_parent->AddChild(this);
}
Transform* Transform::Parent() const { return m_parent; }

/**
 * \brief Adds a new child to this transform
 */
void Transform::AddChild(Transform* child)
{
    //find if alredy a child
    auto result{std::find_if( std::begin(m_children), std::end(m_children), [&child](Transform* stored_child)->bool { return child->InstanceID() == stored_child->InstanceID(); } )};

    if(result == std::end(m_children))//not found
        m_children.push_back(child);
}

Transform* Transform::RemoveChild(UID id)
{
    //find child
    auto result{std::find_if( std::begin(m_children), std::end(m_children), [&id](Transform* stored_child)->bool { return id == stored_child->InstanceID(); } )};

    if(result != std::end(m_children))//found
    {
        auto child{ *result };

        m_children.erase(result);

        return child;
    }

    return nullptr;
}

/**
 * \brief Return a ref to the vector hlding all of this transform children
 */
std::vector<Transform*>* Transform::Children() { return &m_children; }
//</f> /Hierarchy (parents/children)

//<f> Ownership & UID
UID Transform::InstanceID() const { return m_instance_id; }

Object* Transform::Owner() const { return m_owner; }
void Transform::Owner(Object* owner) { m_owner = owner; }
//</f> /Ownership

//<f> AnchorType
AnchorType Transform::Anchor() const { return m_anchor_type; }
void Transform::Anchor(AnchorType anchor) { m_anchor_type = anchor; }
//</f> /AnchorType


//<f> Common Functions
/**
 * \brief Ajusts a position vector to a specific anchor.
 * \nUsed for colliders and rendering
 */
Vector3<float> AjustPositionToAnchor(const Vector3<float>& position, const Vector3<float>& size, AnchorType anchor_type)
{
    auto ajusted_position{position};

    switch (anchor_type)
    {
    case AnchorType::Top_Left: break;//do nothing
        case AnchorType::Top_Centre:
            ajusted_position.X( ajusted_position.X() - size.X() / 2.f );
        break;
        case AnchorType::Top_Right:
            ajusted_position.X( ajusted_position.X() - size.X() );
        break;

        case AnchorType::Centre_Left:
            ajusted_position.Y( ajusted_position.Y() - size.Y() / 2.f );
        break;
        case AnchorType::Centre_Centre:
            ajusted_position.X( ajusted_position.X() - size.X() / 2.f );
            ajusted_position.Y( ajusted_position.Y() - size.Y() / 2.f );
        break;
        case AnchorType::Centre_Right:
            ajusted_position.X( ajusted_position.X() - size.X() );
            ajusted_position.Y( ajusted_position.Y() - size.Y() / 2.f );
        break;

        case AnchorType::Bottom_Left:
            ajusted_position.Y( ajusted_position.Y() - size.Y() );
        break;
        case AnchorType::Bottom_Centre:
            ajusted_position.X( ajusted_position.X() - size.X() / 2.f );
            ajusted_position.Y( ajusted_position.Y() - size.Y() );
        break;
        case AnchorType::Bottom_Right:
            ajusted_position.X( ajusted_position.X() - size.X() );
            ajusted_position.Y( ajusted_position.Y() - size.Y() );
        break;
    }

    return ajusted_position;
}
//</f> /Common Functions
