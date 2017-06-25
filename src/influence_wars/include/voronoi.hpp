#ifndef VORONOI_HPP
#define VORONOI_HPP

class Voronoi
{
    public:
        Voronoi();
        virtual ~Voronoi() noexcept;

        Voronoi(const Voronoi& other);
        Voronoi(Voronoi&& other) noexcept;

        Voronoi& operator=(const Voronoi& other);
        Voronoi& operator=(Voronoi&& other) noexcept;
};

#endif //VORONOI_HPP
