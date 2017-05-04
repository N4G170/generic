#include "influence_cell.hpp"
#include <algorithm>
#include <iostream>
InfluenceCell::InfluenceCell(int type, int x, int y, int w, int h): m_type{type}, m_dimensions{x,y,w,h}
{
    m_colour = SelectColour(m_type);
}

InfluenceCell::~InfluenceCell() noexcept
{

}

InfluenceCell::InfluenceCell(const InfluenceCell& other)
{
    m_colour = other.m_colour;
    m_type = other.m_type;
    m_dimensions.x = other.m_dimensions.x;
}

InfluenceCell::InfluenceCell(InfluenceCell&& other) noexcept
{
    m_type = std::move(other.m_type);
    m_colour = std::move(other.m_colour);
    m_dimensions = std::move(other.m_dimensions);
    // n = std::move(other.n);
}

InfluenceCell& InfluenceCell::operator= (const InfluenceCell& other)
{
    InfluenceCell tmp(other);
    *this = std::move(tmp);

    return *this;
}

InfluenceCell& InfluenceCell::operator= (InfluenceCell &&other) noexcept
{
    return *this;
}

void InfluenceCell::Render(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_colour.r, m_colour.g, m_colour.b, m_colour.a);
    SDL_RenderFillRect(renderer, &m_dimensions);
}

void InfluenceCell::Type(const int& type)
{
    m_type = type;
    m_colour = SelectColour(m_type);
}

void InfluenceCell::Print() const
{
    std::cout<<"{"<< m_dimensions.x <<", "<< m_dimensions.y <<", "<< m_dimensions.w <<", "<< m_dimensions.h <<"}"<<std::endl;
}

SDL_Colour InfluenceCell::SelectColour(int type)
{
    switch (type)
    {
        case 1: return {110,139,61,255};//DarkOliveGreen4
        case 2: return {189,183,107,255};//DarkKhaki

        case 3: return {222,184,135,255};//burlywood
        case 4: return {139,115,85,255};//burlywood4

        case 5: return {142,107,35,255};//Sienna brown
        case 6: return {107,66,38,255};//Semi-Sweet Chocolate brown

        case 7: return {119,119,119,255};//grey
        case 8: return {85,85,85,255};//darker grey

        case 9: return {34,34,34,255};//even darker grey
        case 10: return {245,255,250,255};//MintCream

        default: return {0,0,0,255};
    }
}
