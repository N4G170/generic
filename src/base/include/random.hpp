#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

std::default_random_engine& RandomEngine();

void GenerateNewSeed();

//** \brief Max inclusive */
int Random(int min, int max);
//** \brief Max inclusive */
int Random(int min, int max, uint32_t seed);

//** \brief Max inclusive */
float Random(float min, float max);
//** \brief Max inclusive */
float Random(float min, float max, uint32_t seed);

//** \brief Max inclusive */
double Random(double min, double max);
//** \brief Max inclusive */
double Random(double min, double max, uint32_t seed);


#endif //RANDOM_HPP
