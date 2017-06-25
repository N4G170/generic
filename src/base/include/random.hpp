#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

std::default_random_engine& RandomEngine();

void GenerateNewSeed();

//Max inclusive
int Random(int min, int max);
//Max inclusive
int Random(int min, int max, uint32_t seed);

//Max inclusive
double Random(double min, double max);
//Max inclusive
double Random(double min, double max, uint32_t seed);


#endif //RANDOM_HPP
