#ifndef MAP_HPP
#define MAP_HPP

#include "script.hpp"
#include "system_manager.hpp"
#include "map_structs.hpp"
#include <vector>

class Map : public Script
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        explicit Map(SystemManager* system_manager);
        /** brief Default destructor */
        virtual ~Map() noexcept;

        /** brief Copy constructor */
        Map(const Map& other);
        /** brief Move constructor */
        Map(Map&& other) noexcept;

        /** brief Copy operator */
        Map& operator= (const Map& other);
        /** brief Move operator */
        Map& operator= (Map&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;
        //</f> /Virtual Methods

        //<f> Methods
        void BuildMap();
        //</f> /Methods

        //<f> Getters/Setters

        //</f> /Getters/Setters

    protected:
        // vars and stuff
        SystemManager* m_system_manager;
        MapStats m_map_stats;
    private:
};

#endif //MAP_HPP
