#ifndef ARMY_HPP
#define ARMY_HPP

#include "behaviour_script.hpp"
#include "vector3.hpp"
#include <functional>
#include <vector>
#include <utility>
#include "map.hpp"

class Army: public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Army(MapStats* map_stats);
        /** brief Default destructor */
        virtual ~Army() noexcept;

        /** brief Copy constructor */
        Army(const Army& other);
        /** brief Move constructor */
        Army(Army&& other) noexcept;

        /** brief Copy operator */
        Army& operator= (const Army& other);
        /** brief Move operator */
        Army& operator= (Army&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        void Destination(const Vector3<float>& destination);
        void Path(const std::vector<Vector3<float>>& path);

        void Move();
        void Stop();
        void Moving(bool moving);
        bool Moving() const;

        void Colour(const SDL_Colour& colour);
        SDL_Colour Colour() const;
        void ArmyIndex(int index);
        int ArmyIndex() const;
        //</f> /Getters/Setters

        //<f> Methods
        void Start();
        //</f> /Methods

    protected:
        // vars and stuff
        //<f> Movement
        bool m_moving;
        Vector3<float> m_velocity;
        Vector3<float> m_direction;
        Vector3<float> m_destination;
        float m_position_error_squared;
        //</f> /Movement

        //<f> Map & Path
        MapStats* m_map_stats;
        std::vector<int> m_path;
        std::vector<Vector3<float>> m_path_positions;
        int m_current_path_index;
        int m_start_cell_index;
        int m_target_cell_index;
        //</f> /Map & Path

        SDL_Colour m_colour;
        int m_army_index;

        void NewStartingPosition();
        void CalculateDirection(const Vector3<float>& destination);
        void NewPath();
    private:
};

#endif //ARMY_HPP
