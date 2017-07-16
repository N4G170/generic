#include "sdl_gui_element.hpp"
#include <utility>
#include "sdl_gui_utils.hpp"

namespace sdl_gui
{
//<f> Constructors & operator=
GuiElement::GuiElement(GuiMainPointers main_pointers, const Position& position, const Dimensions& size): m_uid{GenerateUID()}, m_transform{this}, m_size{size},
    m_main_pointers{main_pointers}, m_render{true}, m_active{true}, m_focused{false}, m_parent{nullptr}
{
    m_transform.LocalPosition(position);
}

GuiElement::~GuiElement() noexcept {}

GuiElement::GuiElement(const GuiElement& other) : m_uid{GenerateUID()}, m_transform{other.m_transform},
    m_size{other.m_size}, m_main_pointers{other.m_main_pointers},
    m_render{other.m_render}, m_active{other.m_active}, m_focused{other.m_focused},
    m_parent{other.m_parent}, m_children{other.m_children} {}

GuiElement::GuiElement(GuiElement&& other) noexcept : m_uid{std::move(other.m_uid)}, m_transform{std::move(other.m_transform)},
    m_size{std::move(other.m_size)}, m_main_pointers{std::move(other.m_main_pointers)},
    m_render{std::move(other.m_render)}, m_active{std::move(other.m_active)}, m_focused{std::move(other.m_focused)},
    m_parent{std::move(other.m_parent)}, m_children{std::move(other.m_children)} {}

GuiElement& GuiElement::operator= (const GuiElement& other)
{
    if(this != &other)
    {
        GuiElement tmp{other};//copy, will generate new uid
        *this = std::move(tmp);
    }
    return *this;
}

GuiElement& GuiElement::operator= (GuiElement&& other)
{
    if(this != &other)
    {
        this->m_uid = std::move(other.m_uid);
        this->m_transform = std::move(other.m_transform);
        this->m_size = std::move(other.m_size);
        this->m_main_pointers = std::move(other.m_main_pointers);
        this->m_render = std::move(other.m_render);
        this->m_active = std::move(other.m_active);
        this->m_focused = std::move(other.m_focused);
        this->m_parent = std::move(other.m_parent);
        this->m_children =std::move(other.m_children);
    }
    return *this;
}
//</f>

//<f> Virtual Funtions
void GuiElement::Input(const SDL_Event& event) {}

void GuiElement::ClearInput() {}

void GuiElement::FixedLogic(float fixed_delta_time) {}

void GuiElement::Logic(float delta_time) {}

void GuiElement::Render(float delta_time) { Render(delta_time, m_main_pointers.main_camera_ptr); }

void GuiElement::Render(float delta_time, Camera* camera) {}
//</f>

//<f> Render
SDL_Rect GuiElement::RenderRect()
{
    Position position{GlobalPosition()};
    // return {static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(m_size.w), static_cast<int>(m_size.h)};
    return RectFromFloats(position.x, position.y, m_size.w, m_size.h);
}
//</f>

//<f> Position, Size & Transform interface
void GuiElement::CentreInParent()
{
    if(m_parent != nullptr)
    {
        auto parent_size{m_parent->Size()};

        //parent midpoint(local)
        Position midpoint{ parent_size.w / 2, parent_size.h / 2};
        this->LocalPosition({midpoint.x - Size().w / 2, midpoint.y - Size().h / 2});
    }
}
//</f>

//<f> Interaction & Colliders
/* Add Box collider */
void GuiElement::AddGuiCollider(const Position& local_position, const Dimensions& size, GuiTransform* owner_transform)
{
    m_colliders.emplace_back(local_position, size, owner_transform);
}
/* Add Circle collider */
void GuiElement::AddGuiCollider(const Position& local_position, int circle_radius, GuiTransform* owner_transform)
{
    m_colliders.emplace_back(local_position, circle_radius, owner_transform);
}
//</f>

//<f> Parent & Children
/**
 * Sets this element parent. Will, also, set the parent in the transform
 */
void GuiElement::Parent(GuiElement* parent)
{
    //update transform
    // m_transform.Parent(parent->TransformPtr());

    if(parent != nullptr)//new parent
    {
        if(m_parent != nullptr)//we swap parents
        {
            //remove US as a child link
            m_parent->RemoveChild(ElementUID());
            //set new parent
            m_parent = parent;
            //set new child link
            m_parent->AddChild(this);
        }
        else//we add new parent
        {
            m_parent = parent;//set new parent
            //set new child link
            m_parent->AddChild(this);
        }
    }
    else if(m_parent != nullptr)//we remove current parent
    {
        //remove previous child link
        m_parent->RemoveChild(ElementUID());
        //set new parent
        m_parent = parent;
    }
    //else we do nothing (means that m_parent == parent == nullptr)

}
/**
 * \brief Take ownership of the element
 */
void GuiElement::AddChild(GuiElement* element)
{
    auto found = m_children.find(element->ElementUID());
    if(found != std::end(m_children))//already a child
        return;

    //add child
    m_children.emplace(element->ElementUID(), element);//calls GuiElement move constructor and create pointer
}

void GuiElement::RemoveChild(UID uid)
{
    m_children.erase(uid);
}
//</f>

}//namespace
