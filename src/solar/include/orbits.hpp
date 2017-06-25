#ifndef ORBITS_hPP
#define ORBITS_hPP

#include <vector>
#include "vector2.hpp"

void GenerateOrbit(std::vector<Vector2<float>>& orbit_storage, float perihelion, float aphelion, float rad_angle_jump = 0.02);
void GenerateMercuryOrbit(std::vector<Vector2<float>>& orbit_storage);
void GenerateVenusOrbit(std::vector<Vector2<float>>& orbit_storage);

#endif //ORBITS_hPP
