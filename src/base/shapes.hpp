#ifndef SHAPES_HPP
#define SHAPES_HPP
#include "constants.hpp"
#include <vector>

// struct Rectalgle

void DrawCircunference(SDL_Renderer* renderer, int centre_x, int centre_y, int radius, SDL_Colour colour = Colour::Black);
void DrawCircle(SDL_Renderer* renderer, int centre_x, int centre_y, int radius, SDL_Colour border_colour = Colour::Black, SDL_Colour fill_colour = Colour::Black);
void GenerateCircunferenceFirstOctantSDLPoints(int radius, std::vector<SDL_Point>& points);
void GenerateCircleFirstOctantSDLPoints(int radius, std::vector<SDL_Point>& points);

// void DrawRectangle();
// void DrawFillRectangle();
#endif //SHAPES_HPP
