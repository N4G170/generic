#include "army.hpp"
#include <utility>
#include "object.hpp"
#include <iostream>
#include "random.hpp"
#include "constants.hpp"
#include "map.hpp"
#include "pathfind.hpp"
#include "debug_render.hpp"

//<f> Constructors & operator=
Army::Army(MapStats* map_stats): BehaviourScript{},
    m_moving{false}, m_velocity{1,1,1}, m_direction{0,0,0}, m_destination{0,0,0}, m_position_error_squared{15},
    m_map_stats{map_stats}, m_path{}, m_path_positions{}, m_current_path_index{0}, m_target_cell_index{-1}, m_colour{255,255,255,255}, m_army_index{0}
{

}

Army::~Army() noexcept
{

}

Army::Army(const Army& other)
{

}

Army::Army(Army&& other) noexcept
{

}

Army& Army::operator=(const Army& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Army& Army::operator=(Army&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=

//<f> Virtual Methods
Script* Army::Clone() { return new Army{*this};}

void Army::Update(float delta_time)
{
    if(m_owner == nullptr)
        return;

    if(m_moving)
    {
        auto position{m_owner->TransformPtr()->LocalPosition()};

        if(position.DistanceSquared(m_destination) > m_position_error_squared)//did not reach destination
        {
            position += m_direction * m_velocity * 2;
        }
        else
        {
            position = m_destination;
            m_moving = false;

            //increase path index
            ++m_current_path_index;

            if(m_current_path_index >= m_path_positions.size() - 1)//reached last valid position
            {
                m_current_path_index = 0;

                //calculate new path
                m_start_cell_index = m_target_cell_index;
                NewPath();
                CalculateDirection( m_path_positions[m_current_path_index + 1] );
                Move();
            }
            else
            {
                CalculateDirection( m_path_positions[m_current_path_index + 1] );
                Move();
            }
        }
        m_owner->TransformPtr()->LocalPosition(position);

        //set path debug render
        for(auto i{0}; i < m_path_positions.size() - 1; ++i)
        {
            auto parent_position { m_owner->TransformPtr()->Parent()->LocalPosition() };
            DebugRender::Instance()->RenderDrawLine(m_path_positions[i] + parent_position, m_path_positions[i+1] + parent_position, m_colour, m_army_index);
        }
    }
}
//</f> /Virtual Methods

//<f> Getters/Setters
void Army::Move() { m_moving = true; }
void Army::Stop() { m_moving = false; }
void Army::Moving(bool moving) { m_moving = moving; }
bool Army::Moving() const { return m_moving; }
void Army::Colour(const SDL_Colour& colour) { m_colour = colour; }
SDL_Colour Army::Colour() const { return m_colour; }
void Army::ArmyIndex(int index) { m_army_index = index; }
int Army::ArmyIndex() const { return m_army_index; }
//</f> /Getters/Setters

void Army::Start()
{
    NewStartingPosition();
    NewPath();
    CalculateDirection( m_path_positions[1] );
    Move();
}

void Army::CalculateDirection(const Vector3<float>& destination)
{
    m_destination = destination;

    auto position{m_owner->TransformPtr()->LocalPosition()};
    m_direction = m_destination - position;
    m_direction.Z(-0.5f);
    m_direction.Normalize();
}

void Army::NewStartingPosition()
{
    if(m_map_stats->positions.empty())
    {
        m_owner->TransformPtr()->LocalPosition({0,0,0});
    }
    else
    {
        while(true)
        {
            auto random{Random(0, m_map_stats->positions.size() - 1)};

            if(m_map_stats->map_costs[random] > 0)//valid cell
            {
                auto position{m_map_stats->positions[random]};
                position.Z(-0.5f);
                m_owner->TransformPtr()->LocalPosition(position);

                m_target_cell_index = m_start_cell_index = random;
                return;
            }
        }
    }
}

void Army::NewPath()
{
    while(true)
    {
        auto random{Random(0, m_map_stats->map_costs.size() - 1)};

        if(m_map_stats->map_costs[random] > 0 )//valid cell
        {
            m_path = FindPath(GetCoordinateX(m_start_cell_index, m_map_stats->map_width_cell_count),
                            GetCoordinateY(m_start_cell_index, m_map_stats->map_width_cell_count),
                            GetCoordinateX(random, m_map_stats->map_width_cell_count),
                            GetCoordinateY(random, m_map_stats->map_width_cell_count),
                            // m_map_stats->map_costs.data(), m_map_stats->map_width_cell_count, m_map_stats->map_height_cell_count, NeighbourSearchType::QUARTILE);
                            m_map_stats->map_costs.data(), m_map_stats->map_width_cell_count, m_map_stats->map_height_cell_count, NeighbourSearchType::OCTILE_CORNER_CUT);
            break;
        }
    }

    //convert path indeces to positions
    m_path_positions.clear();
    for(auto i : m_path)
    {
        auto position{m_map_stats->positions[i]};
        position.Z(-0.5f);
        m_path_positions.push_back(position);
    }

    m_start_cell_index = m_path.front();
    m_target_cell_index = m_path.back();
}
