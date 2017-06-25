#include "shapes.hpp"
#include "SDL.h"

void DrawCircunference(SDL_Renderer* renderer, int centre_x, int centre_y, int radius, SDL_Colour colour)
{
    SDL_SetRenderDrawColor( renderer, colour.r, colour.g, colour.b, colour.a );

    //draw circunference
    int cos45 = static_cast<int>(SquareRoot(2)/2 * radius);
    int squared_radius = radius * radius;
    for (int x = 0; x <= cos45; ++x)
    {
        int y = static_cast<int>(SquareRoot((double)squared_radius - x * x));//if + makes vegeta head vein
        SDL_RenderDrawPoint(renderer, x + centre_x, y + centre_y);
        SDL_RenderDrawPoint(renderer, x + centre_x, -y + centre_y);
        SDL_RenderDrawPoint(renderer, -x + centre_x, y + centre_y);
        SDL_RenderDrawPoint(renderer, -x + centre_x, -y + centre_y);

        SDL_RenderDrawPoint(renderer, y + centre_x, x + centre_y);
        SDL_RenderDrawPoint(renderer, y + centre_x, -x + centre_y);
        SDL_RenderDrawPoint(renderer, -y + centre_x, x + centre_y);
        SDL_RenderDrawPoint(renderer, -y + centre_x, -x + centre_y);
    }
}

void DrawCircle(SDL_Renderer* renderer, int centre_x, int centre_y, int radius, SDL_Colour border_colour, SDL_Colour fill_colour)
{
    // //draw circunference
    // DrawCircunference(renderer, centre_x, centre_y, radius, border_colour);

    SDL_SetRenderDrawColor( renderer, fill_colour.r, fill_colour.g, fill_colour.b, fill_colour.a );

    //fill circle
    int diagonal = radius * 2;//inner square diagonal
    int side = diagonal / SquareRoot(2);//inner square side
    int half_side = side / 2;
    int squared_radius = radius * radius;

    SDL_Rect square{ centre_x - half_side, centre_y - half_side, side, side };
    SDL_RenderFillRect(renderer, &square);

    for(int x = -half_side; x <= half_side; ++x)
    {
        for(int y = half_side; y <= radius; ++y)
        {
            if(x*x + y*y <= squared_radius)
            {
                SDL_RenderDrawPoint(renderer, x + centre_x, y + centre_y);
                SDL_RenderDrawPoint(renderer, x + centre_x, -y + centre_y);
                SDL_RenderDrawPoint(renderer, y + centre_x, x + centre_y);
                SDL_RenderDrawPoint(renderer, -y + centre_x, x + centre_y);
            }
        }
    }

    //draw circunference - at the end to be able to render a border with another color
    DrawCircunference(renderer, centre_x, centre_y, radius, border_colour);
}

void GenerateCircunferenceFirstOctantSDLPoints(int radius, std::vector<SDL_Point>& points)
{
    //draw circunference
    int cos45 = static_cast<int>(SquareRoot(2)/2 * radius);
    int squared_radius = radius * radius;

    for (int x = 0; x <= cos45; ++x)
        points.push_back( {x, -(static_cast<int>(SquareRoot((double)squared_radius - x * x))) });//O1
}

void GenerateCircleFirstOctantSDLPoints(int radius, std::vector<SDL_Point>& points)
{
    GenerateCircunferenceFirstOctantSDLPoints(radius, points);

    //fill circle
    int squared_radius = radius * radius;
    int cos45 = static_cast<int>(SquareRoot(2)/2 * radius);

    for(int x = 0; x <= radius; ++x)
    {
        for(int y = 0; y <= cos45 && y <= x; ++y)
        {
            if(x*x + y*y <= squared_radius)
            {
                points.push_back({x, -y});//O1
            }
        }
    }
}
