#ifndef INFLUENCE_CELL_HPP
#define INFLUENCE_CELL_HPP

#include <SDL2/SDL.h>

class InfluenceCell
{
    public:
        InfluenceCell(int type, int x, int y, int w, int h);
        virtual ~InfluenceCell() noexcept;
        InfluenceCell(const InfluenceCell& other);
        InfluenceCell(InfluenceCell&& other) noexcept;

        InfluenceCell& operator= (const InfluenceCell& other);
        InfluenceCell& operator= (InfluenceCell&& other) noexcept;

        void Render(SDL_Renderer* renderer);

        void Type(const int& type);
// double n;
        void Print() const;
    private:
        int m_type;
        SDL_Colour m_colour;
        SDL_Rect m_dimensions;

        SDL_Colour SelectColour(int type);


};

#endif //INFLUENCE_CELL_HPP
