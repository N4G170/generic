#include "map.hpp"
#include <utility>
#include <vector>
#include "image.hpp"
#include "constants.hpp"

#if defined(__linux__) || defined(__gnu_linux__)
#include "sol.hpp"
#endif

#include "army.hpp"
#include "random.hpp"
// #include "pathfind.hpp"
#include "static_canvas.hpp"
#include "utils.hpp"

//<f> Constructors & operator=
Map::Map(SystemManager* system_manager): Script{}, m_system_manager{system_manager}
{

}

Map::~Map() noexcept
{

}

Map::Map(const Map& other): Script{other}, m_system_manager{other.m_system_manager}
{

}

Map::Map(Map&& other) noexcept: Script{std::move(other)}, m_system_manager{std::move(other.m_system_manager)}
{

}

Map& Map::operator=(const Map& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Map& Map::operator=(Map&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
        m_system_manager = std::move(other.m_system_manager);
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Map::Clone() { return new Map{*this}; }
//</f> /Virtual Methods

//<f> Methods
#if defined(__linux__) || defined(__gnu_linux__)
void Map::BuildMap()
{
    //<f> Map

    //load lua
    sol::state lua_state;

    lua_state.script_file("data/lua/map.lua");

    sol::table map_table = lua_state["map"];

    std::vector<unsigned char> map;

    //convert table to vector
    for(auto i{1}; i<=map_table.size(); ++i)//needs to be <= as size value is the last valid index (lua stuff)
        map.push_back( static_cast<unsigned char>(map_table[i]) );

    m_map_stats.cell_width = lua_state["cell_width"];
    m_map_stats.cell_height = lua_state["cell_height"];
    m_map_stats.map_width_cell_count = lua_state["map_width_cell_count"];
    m_map_stats.map_height_cell_count = lua_state["map_height_cell_count"];
    m_map_stats.map_width =lua_state["map_width"];
    m_map_stats.map_height =lua_state["map_height"];

    sol::table costs_table = lua_state["costs"];
    sol::table colour_table = lua_state["cell_colours"];

    //centre map
    // m_owner->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto map_x = window_centre_x - m_map_stats.map_width /2;
    auto map_y = window_centre_y - m_map_stats.map_height /2;
    m_owner->TransformPtr()->LocalPosition({map_x, map_y, 1});
    // m_owner->TransformPtr()->LocalScale({m_map_stats.map_width, m_map_stats.map_height, 1});

    //map image
    // auto custom_image{new CustomTexture{m_system_manager->Renderer(), (int)m_map_stats.map_width, (int)m_map_stats.map_height}};

    auto obj = m_system_manager->Objects()->CreateObject();
    auto canvas = new StaticCanvas{m_system_manager};
    obj->AddScript(canvas);
    obj->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 1});
    obj->TransformPtr()->LocalScale({m_map_stats.map_width, m_map_stats.map_height,0});
    canvas->CanvasSize({m_map_stats.map_width, m_map_stats.map_height,0});

    auto cell_obj{m_system_manager->Objects()->CreateObject()};
    auto cell_img{new Image{m_system_manager}};
    cell_obj->AddScript(cell_img);
    cell_obj->Disable();

    for(unsigned int i{0}; i < map.size(); ++i)//create cells
    {
        auto x{(i % m_map_stats.map_width_cell_count) * m_map_stats.cell_width};
        auto y{(i / m_map_stats.map_width_cell_count) * m_map_stats.cell_height};


        cell_obj->TransformPtr()->LocalPosition({x, y, 0});
        cell_obj->TransformPtr()->LocalScale({m_map_stats.cell_width, m_map_stats.cell_height, 0});

        SDL_Colour colour{ colour_table[map[i]][1], colour_table[map[i]][2], colour_table[map[i]][3], colour_table[map[i]][4] };

        cell_img->ColourModulation(colour);
        canvas->AddImage(cell_img);

        m_map_stats.positions.push_back({x, y, 2});
        m_map_stats.map_costs.push_back(costs_table[map[i]]);
    }
    //</f> /Map

    //<f> Armies
    sol::table armies = lua_state["armies"];

    auto armies_obj = m_system_manager->Objects()->CreateObject();
    armies_obj->TransformPtr()->LocalPosition({window_centre_x - m_map_stats.map_width/2, window_centre_y - m_map_stats.map_height/2, 0});

    // for(auto i{1}; i<=1; ++i)
    for(auto i{1}; i<=armies.size(); ++i)
    {
        sol::table army_table = armies[i];

        std::string img_path = army_table["image"];

        sol::table colour_table = army_table["colour"];
        SDL_Colour colour{ colour_table[1], colour_table[2], colour_table[3], colour_table[4] };

        sol::table size_table = army_table["size"];
        Vector3<float> size{ size_table[1], size_table[2], size_table[3] };

        //create army
        auto army_obj{m_system_manager->Objects()->CreateObject()};
        army_obj->TransformPtr()->Parent(armies_obj->TransformPtr());
        auto army_img{new Image{m_system_manager}};

        army_img->SetImage(img_path);
        army_img->ColourModulation(colour);
        army_obj->AddScript(army_img);
        army_obj->TransformPtr()->GlobalScale(size);
        army_obj->TransformPtr()->Anchor(AnchorType::Centre_Centre);

        auto army_script{new Army{&m_map_stats}};
        army_obj->AddScript(army_script);
        army_script->Start();
        army_script->Colour(colour);
        army_script->ArmyIndex(i);
    }
    //</f> /Armies

}

#elif defined(_WIN32) || defined(_WIN64)
void Map::BuildMap()
{
    //<f> Map

    std::vector<unsigned char> map = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 3, 3, 3, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 3, 3, 3, 3, 3, 3, 0, 2, 0, 3, 0, 2, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 2, 8, 9, 9, 0,
            0, 3, 3, 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 3, 3, 0, 0, 0, 2, 0, 3, 0, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 2, 8, 8, 8, 0,
            0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 2, 2, 2, 2, 2, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 2, 2, 2, 3, 2, 3, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 8, 8, 8, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 1, 1, 2, 1, 2, 2, 0,
            0, 9, 9, 9, 9, 9, 9, 9, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 0, 0, 2, 0, 0, 0, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 1, 1, 1, 1, 1, 1, 2, 2, 0,
            0, 9, 3, 3, 3, 3, 3, 9, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 2, 2, 2, 2, 3, 0, 3, 0, 2, 3, 3, 0, 3, 0, 3, 0, 2, 0, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 1, 6, 6, 6, 2, 2, 2, 2, 0,
            0, 9, 3, 8, 8, 8, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 2, 2, 2, 2, 3, 0, 0, 0, 2, 0, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 1, 6, 6, 6, 6, 1, 2, 1, 0,
            0, 9, 3, 8, 9, 8, 3, 9, 9, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 1, 6, 6, 1, 1, 1, 1, 1, 0,
            0, 9, 3, 8, 9, 8, 3, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 5, 1, 1, 1, 1, 2, 2, 5, 3, 0,
            0, 9, 3, 8, 9, 8, 3, 3, 3, 3, 3, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 5, 2, 2, 2, 2, 2, 5, 5, 3, 0,
            0, 9, 3, 8, 8, 8, 9, 9, 9, 9, 9, 9, 0, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 8, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 1, 1, 1, 1, 1, 3, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 3, 2, 2, 8, 8, 8, 8, 8, 8, 8, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 8, 8, 8, 1, 1, 1, 3, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 1, 1, 1, 1, 1, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 8, 8, 8, 8, 8, 9, 9, 8, 9, 9, 9, 9, 9, 8, 3, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 8, 8, 8, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 8, 3, 8, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 2, 2, 2, 2, 2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 2, 8, 8, 9, 9, 9, 9, 9, 8, 9, 9, 9, 8, 8, 8, 3, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 2, 2, 2, 2, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 8, 8, 8, 8, 8, 8, 8, 1, 1, 1, 3, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 0,
            0, 2, 2, 2, 2, 2, 2, 1, 3, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 8, 8, 8, 8, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0,
            0, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 0,
            0, 1, 1, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
            0, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
            0, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
            0, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
            0, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0,
            0, 6, 6, 6, 6, 6, 6, 6, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0,
            0, 6, 6, 6, 6, 6, 6, 6, 3, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 7, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
            0, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 0,
            0, 7, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 0, 0, 0, 0, 0, 0, 0, 8, 7, 7, 0,
            0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 0, 7, 7, 7, 7, 7, 0, 8, 7, 7, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 0, 7, 4, 4, 4, 7, 0, 8, 7, 7, 0,
            0, 0, 0, 8, 8, 8, 0, 3, 3, 3, 0, 3, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 0, 7, 4, 4, 4, 7, 0, 8, 7, 7, 0,
            0, 0, 0, 8, 1, 8, 0, 3, 0, 3, 0, 3, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 0, 7, 7, 7, 7, 7, 0, 8, 7, 7, 0,
            0, 3, 3, 8, 8, 8, 8, 3, 8, 3, 8, 3, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 8, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 0,
            0, 3, 0, 0, 0, 8, 0, 3, 0, 3, 0, 3, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 0,
            0, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
          };

    m_map_stats.cell_width = 16;
    m_map_stats.cell_height = 16;
    m_map_stats.map_width_cell_count = 75;
    m_map_stats.map_height_cell_count = 45;
    m_map_stats.map_width = m_map_stats.cell_width * m_map_stats.map_width_cell_count;
    m_map_stats.map_height = m_map_stats.cell_height * m_map_stats.map_height_cell_count;

    std::vector<int> costs = {
        0, // 0 means invalid path
        3, // grassland
        5, // tall grass/trees
        1, // dirt road
        2, // Beach sand
        5, // Desert Sand
        4, // Shallow water
        6, // Deep water
        5, // Rocky path
        7  // Boulders
    };

    std::vector<SDL_Colour> cell_colours = {
        { 64,  64,  64, 255},
        { 44, 176,  55, 255},
        { 31, 138,  19, 255},
        {155, 118,  83, 255},
        {194, 178, 128, 255},
        {236, 213,  64, 255},
        { 64, 164, 223, 255},
        { 30,  95,  90, 255},
        { 90,  77,  65, 255},
        {114, 116, 114, 255}
    };

    //centre map
    // m_owner->TransformPtr()->Anchor(AnchorType::Centre_Centre);
    auto map_x = window_centre_x - m_map_stats.map_width /2;
    auto map_y = window_centre_y - m_map_stats.map_height /2;
    m_owner->TransformPtr()->LocalPosition({map_x, map_y, 1});
    // m_owner->TransformPtr()->LocalScale({m_map_stats.map_width, m_map_stats.map_height, 1});

    //map image
    // auto custom_image{new CustomTexture{m_system_manager->Renderer(), (int)m_map_stats.map_width, (int)m_map_stats.map_height}};

    auto obj = m_system_manager->Objects()->CreateObject();
    auto canvas = new StaticCanvas{m_system_manager};
    obj->AddScript(canvas);
    obj->TransformPtr()->LocalPosition({window_centre_x, window_centre_y, 1});
    obj->TransformPtr()->LocalScale({m_map_stats.map_width, m_map_stats.map_height,0});
    canvas->CanvasSize({m_map_stats.map_width, m_map_stats.map_height,0});

    auto cell_obj{m_system_manager->Objects()->CreateObject()};
    auto cell_img{new Image{m_system_manager}};
    cell_obj->AddScript(cell_img);
    cell_obj->Disable();

    for(unsigned int i{0}; i < map.size(); ++i)//create cells
    {
        auto x{(i % m_map_stats.map_width_cell_count) * m_map_stats.cell_width};
        auto y{(i / m_map_stats.map_width_cell_count) * m_map_stats.cell_height};


        cell_obj->TransformPtr()->LocalPosition({x, y, 0});
        cell_obj->TransformPtr()->LocalScale({m_map_stats.cell_width, m_map_stats.cell_height, 0});

        SDL_Colour colour{ cell_colours[map[i]].r, cell_colours[map[i]].g, cell_colours[map[i]].b, cell_colours[map[i]].a };

        cell_img->ColourModulation(colour);
        canvas->AddImage(cell_img);

        m_map_stats.positions.push_back({x, y, 2});
        m_map_stats.map_costs.push_back(costs[map[i]]);
    }
    //</f> /Map

    //<f> Armies
    struct ArmyStruct
    {
        std::string image = "data/img/circle.png";
        SDL_Colour colour = {255,0,0,255};
        Vector3<float> size = {16, 16, 0};
        ArmyStruct(const std::string& img, SDL_Colour clr, Vector3<float> dimensions): image{img}, colour{clr.r, clr.g, clr.b, clr.a}, size{dimensions} {}
    };

    std::vector<ArmyStruct> armies =
    {
        { "data/img/circle.png", {255,0,0,255}, {16, 16, 0} },
        { "data/img/circle.png", {0,255,0,255}, {16, 16, 0} },
        { "data/img/circle.png", {0,0,255,255}, {16, 16, 0} },
        { "data/img/circle.png", {255,255,0,255}, {16, 16, 0}}
    };

    auto armies_obj = m_system_manager->Objects()->CreateObject();
    armies_obj->TransformPtr()->LocalPosition({window_centre_x - m_map_stats.map_width/2, window_centre_y - m_map_stats.map_height/2, 0});

    // for(auto i{1}; i<=1; ++i)
    for(auto i{0}; i < armies.size(); ++i)
    {
        //create army
        auto army_obj{m_system_manager->Objects()->CreateObject()};
        army_obj->TransformPtr()->Parent(armies_obj->TransformPtr());
        auto army_img{new Image{m_system_manager}};

        army_img->SetImage(armies[i].image);
        army_img->ColourModulation(armies[i].colour);
        army_obj->AddScript(army_img);
        army_obj->TransformPtr()->GlobalScale(armies[i].size);
        army_obj->TransformPtr()->Anchor(AnchorType::Centre_Centre);

        auto army_script{new Army{&m_map_stats}};
        army_obj->AddScript(army_script);
        army_script->Start();
        army_script->Colour(armies[i].colour);
        army_script->ArmyIndex(i);
    }
    //</f> /Armies

}
#endif


//</f> /Methods
