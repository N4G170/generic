#include "utils.hpp"
#include "constants.hpp"

bool PointInsideRect(const SDL_Rect& rect, const int& point_x, const int& point_y)
{
    return (point_x > rect.x && point_x <= rect.x + rect.w) && (point_y > rect.y && point_y <= rect.y + rect.h);
}

int Lerp(const int& start, const int& end, const float& t)
{
    return static_cast<int>((1-t) * start + t * end);
}

float Lerp(const float& start, const float& end, const float& t)
{
    return (1-t) * start + t * end;
    //return start + (end - start) * t;//damn precision errors
}

double Lerp(const double& start, const double& end, const double& t)
{
    return (1-t) * start + t * end;
    //return start + (end - start) * t;//damn precision errors
}

float RadiansToDegrees(float radians)
{
    return radians * 180 / Math::PI;
}

float DegreesToRadians(float degrees)
{
    return degrees * Math::PI / 180;
}

//rect casts
SDL_Rect RectFromFloats(float x, float y, float w, float h)
{
    return {static_cast<int>(std::round(x)), static_cast<int>(std::round(y)), static_cast<int>(std::round(w)), static_cast<int>(std::round(h))};
}
