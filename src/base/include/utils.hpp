#ifndef UTILS_HPP
#define UTILS_HPP

#include "SDL.h"


bool PointInsideRect(const SDL_Rect& rect, const int& point_x, const int& point_y);

int Lerp(const int& start, const int& end, const float& t);
float Lerp(const float& start, const float& end, const float& t);
double Lerp(const double& start, const double& end, const double& t);

#endif //UTILS_HPP
