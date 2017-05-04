#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include <vector>
#include "random.hpp"

class PerlinNoise
{
    public:
        PerlinNoise();
        explicit PerlinNoise(uint32_t seed);
        virtual ~PerlinNoise();
        PerlinNoise(const PerlinNoise& other);
        PerlinNoise(PerlinNoise&& other);

        PerlinNoise& operator= (const PerlinNoise& other);
        PerlinNoise& operator= (PerlinNoise&& other);

        void Seed(const uint32_t& seed);
        uint32_t Seed() const;

        double Noise(double x, double y, double z);
        double OctaveNoise(double x, double y, double z, int total_octaves, double persistence);

    private:
        uint32_t m_seed;
        std::vector<int> m_permutations;
        double Fade(double t);
        double Gradient(int hash, double x, double y, double z);

        void GeneratePermutationVector();

        //this functions is declared in the class to remove external dependencies
        double Lerp(const double& start, const double& end, const double& t);
};

#endif//PERLIN_NOISE_HPP
