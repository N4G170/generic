#include "voronoi.hpp"
#include <utility>

Voronoi::Voronoi()
{

}

Voronoi::~Voronoi() noexcept
{

}

Voronoi::Voronoi(const Voronoi& other)
{

}

Voronoi::Voronoi(Voronoi&& other) noexcept
{

}

Voronoi& Voronoi::operator=(const Voronoi& other)
{
    if(this != &other)//not same ref
    {
        Voronoi tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Voronoi& Voronoi::operator=(Voronoi&& other) noexcept
{
    return *this;
}
