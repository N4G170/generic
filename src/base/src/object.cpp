#include "object.hpp"
#include <algorithm>
#include "object_manager.hpp"

//<f> Constructors & operator=
Object::Object(ObjectManager* object_manager): m_instance_id{GenerateUID()}, m_transform{}, m_marked_for_destruction{false}, m_object_manager{object_manager},
    m_access_mutex{}, m_scripts{}, m_behaviour_scripts{},
    m_collider_scripts{}, m_render_scripts{}, m_camera_scripts{}, m_enabled{true}, m_tags{}
{
    m_transform.Owner(this);
}

Object::~Object() noexcept {}

Object::Object(const Object& other): m_instance_id{GenerateUID()}, m_transform{other.m_transform}, m_marked_for_destruction{other.m_marked_for_destruction},
    m_object_manager{other.m_object_manager}, m_access_mutex{}, m_scripts{}, m_behaviour_scripts{},
    m_collider_scripts{}, m_render_scripts{}, m_camera_scripts{}, m_enabled{other.m_enabled}, m_tags{other.m_tags}
{
    m_transform.Owner(this);

    for(auto& script : other.m_scripts)
    {
        auto new_script{script.second->Clone()};
        new_script->Owner(this);
        m_scripts.emplace(script.first, std::unique_ptr<Script>(new_script));

        //store quick pointer
        if(script.first == std::type_index(typeid(BehaviourScript)))
            m_behaviour_scripts.push_back( dynamic_cast<BehaviourScript*>(new_script) );
        else if(script.first == std::type_index(typeid(RenderScript)))
            m_render_scripts.push_back( dynamic_cast<RenderScript*>(new_script) );
        else if(script.first == std::type_index(typeid(Camera)))
            m_camera_scripts.push_back( dynamic_cast<Camera*>(new_script) );
        else if(script.first == std::type_index(typeid(Collider)))
            m_collider_scripts.push_back( dynamic_cast<Collider*>(new_script) );
    }
}

Object::Object(Object&& other) noexcept: m_instance_id{std::move(other.m_instance_id)}, m_transform{std::move(other.m_transform)},
    m_marked_for_destruction{std::move(other.m_marked_for_destruction)}, m_object_manager{std::move(other.m_object_manager)},
    m_access_mutex{}, m_scripts{std::move(other.m_scripts)}, m_behaviour_scripts{},
    m_collider_scripts{}, m_render_scripts{}, m_camera_scripts{},
    m_enabled{std::move(other.m_enabled)}, m_tags{std::move(other.m_tags)}
{
    m_transform.Owner(this);//we need to set owner agin as the this pointer changed
    //update this pointer in scripts
    for(auto& script : m_scripts)
    {
        script.second->Owner(this);

        //store quick pointer
        if(script.first == std::type_index(typeid(BehaviourScript)))
            m_behaviour_scripts.push_back( dynamic_cast<BehaviourScript*>(script.second.get()) );
        else if(script.first == std::type_index(typeid(RenderScript)))
            m_render_scripts.push_back( dynamic_cast<RenderScript*>(script.second.get()) );
        else if(script.first == std::type_index(typeid(Camera)))
            m_camera_scripts.push_back( dynamic_cast<Camera*>(script.second.get()) );
        else if(script.first == std::type_index(typeid(Collider)))
            m_collider_scripts.push_back( dynamic_cast<Collider*>(script.second.get()) );
    }

}

Object& Object::operator=(const Object& other)
{
    if(this != &other)
    {
        auto tmp{other};
        *this = std::move(tmp);
    }
    return *this;
}

Object& Object::operator=(Object&& other) noexcept
{
    if(this != &other)
    {
        m_instance_id = std::move(other.m_instance_id);
        m_transform = std::move(other.m_transform);
        m_marked_for_destruction = std::move(other.m_marked_for_destruction);
        m_object_manager = std::move(other.m_object_manager);
        m_scripts = std::move(other.m_scripts);
        m_enabled = std::move(other.m_enabled);
        m_tags = std::move(other.m_tags);

        m_behaviour_scripts.clear();
        m_collider_scripts.clear();
        m_render_scripts.clear();
        m_camera_scripts.clear();

        //update this pointer in scripts
        for(auto& script : m_scripts)
        {
            script.second->Owner(this);

            //store quick pointer
            if(script.first == std::type_index(typeid(BehaviourScript)))
                m_behaviour_scripts.push_back( dynamic_cast<BehaviourScript*>(script.second.get()) );
            else if(script.first == std::type_index(typeid(RenderScript)))
                m_render_scripts.push_back( dynamic_cast<RenderScript*>(script.second.get()) );
            else if(script.first == std::type_index(typeid(Camera)))
                m_camera_scripts.push_back( dynamic_cast<Camera*>(script.second.get()) );
            else if(script.first == std::type_index(typeid(Collider)))
                m_collider_scripts.push_back( dynamic_cast<Collider*>(script.second.get()) );
        }
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Scrip functions
void Object::Input(const SDL_Event& event)
{
    for(auto& script : m_behaviour_scripts)
        if(script->Enabled())
            script->Input(event);
}
void Object::Update(float delta_time)
{
    for(auto& script : m_behaviour_scripts)
        if(script->Enabled())
            script->Update(delta_time);
}
void Object::FixedUpdate(float fixed_delta_time)
{
    for(auto& script : m_behaviour_scripts)
        if(script->Enabled())
            script->FixedUpdate(fixed_delta_time);
}
void Object::Render(float delta_time)
{
    for(auto& script : m_render_scripts)
        if(script->Enabled())
            script->Render(delta_time);
}
//</f> /Scrip functions

//<f> Script management
/**
 * \brief Remove a script from the object and delete the pointer.
 */
void Object::DeleteScript(UID instance_id)
{
    //lock access to class vars (lock_guard releases itself when funsction returns)
    std::lock_guard<std::mutex> lock(m_access_mutex);

    auto result{ std::find_if(std::begin(m_scripts), std::end(m_scripts), [instance_id](auto& script)->bool { return instance_id == script.second->InstanceID(); } ) };

    if(result != std::end(m_scripts))
        m_scripts.erase(result);
}

/**
 * \brief Return pointer to scripts vector
 */
std::vector<Script*> Object::AllScripts()
{
    std::vector<Script*> scripts;

    for(auto& script : m_scripts)
        scripts.push_back(script.second.get());

    return scripts;
}
//</f> /Script management

//<f> Get/Set
UID Object::InstanceID() const { return m_instance_id; }

Transform* Object::TransformPtr() { return &m_transform; }

bool Object::Enabled() const { return m_enabled; }
void Object::Enabled(bool enabled) { m_enabled = enabled; }

void Object::Enable() { m_enabled = true; }
void Object::Disable() { m_enabled = false; }
//</f> /Get/Set

//<f> Tags
bool Object::AddTag(const std::string& tag)
{
    auto result{std::find_if(std::begin(m_tags), std::end(m_tags), [&tag](auto& stored_tag)->bool { return tag == stored_tag; } )};

    if(result != std::end(m_tags))//already exists
        return false;

    m_tags.push_back(tag);
    return true;
}
bool Object::HasTag(const std::string& tag)
{
    auto result{std::find_if(std::begin(m_tags), std::end(m_tags), [&tag](auto& stored_tag)->bool { return tag == stored_tag; } )};

    if(result != std::end(m_tags))//exists
        return true;
    return false;
}
/**
 * \brief Removes a tag from the object. True on success and false on failure
 * \nFailure will be, probably, because the tag does not exist
 */
bool Object::RemoveTag(const std::string& tag)
{
    auto result{std::find_if(std::begin(m_tags), std::end(m_tags), [&tag](auto& stored_tag)->bool { return tag == stored_tag; } )};

    if(result != std::end(m_tags))//exists
    {
        m_tags.erase(result);
        return true;
    }
    return false;
}
//</f> /Tags

//<f> Destroy
void Object::Destroy()
{
    //destroy any child
    for(auto child : *m_transform.Children())
    {
        child->Owner()->Destroy();
    }

    m_marked_for_destruction = true;

    m_object_manager->HasObjectsToDestroy(true);
}

bool Object::MarkedForDestruction() const { return m_marked_for_destruction; }
//</f> /Destroy
