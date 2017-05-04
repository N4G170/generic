#include "perlin_noise.hpp"
//#include <numeric>
#include <algorithm>
//#include "utils.hpp"

PerlinNoise::PerlinNoise(): m_seed{0}
{
    this->GeneratePermutationVector();
}

PerlinNoise::PerlinNoise(uint32_t seed): m_seed{seed}
{
    this->GeneratePermutationVector();
}

PerlinNoise::~PerlinNoise()
{

}

PerlinNoise::PerlinNoise(const PerlinNoise& other)
{
    m_seed = other.m_seed;
}

PerlinNoise::PerlinNoise(PerlinNoise&& other)
{
    m_seed = std::move(other.m_seed);
}

PerlinNoise& PerlinNoise::operator= (const PerlinNoise& other)
{
    PerlinNoise tmp(other);
    *this = std::move(tmp);
    return *this;
}

PerlinNoise& PerlinNoise::operator= (PerlinNoise&& other)
{
    m_seed = std::move(other.m_seed);
    return *this;
}

void PerlinNoise::Seed(const uint32_t& seed)
{
    m_seed = seed;
    this->GeneratePermutationVector();
}

uint32_t PerlinNoise::Seed() const
{
    return m_seed;
}
#include <iostream>
double PerlinNoise::Noise(double x, double y, double z)
{
    //get the integer part of the coordinates and keeps it no longer than 255
    int x_int = static_cast<int>(x) & 255;
    int y_int = static_cast<int>(y) & 255;
    int z_int = static_cast<int>(z) & 255;

    //get the decimal part of the coordinates. In essence x_decimal = x % 1; but it does not work on doubles
    double x_decimal = x - static_cast<int>(x);
    double y_decimal = y - static_cast<int>(y);
    double z_decimal = z - static_cast<int>(z);

    double x_fade = this->Fade(x_decimal);
    double y_fade = this->Fade(y_decimal);
    double z_fade = this->Fade(z_decimal);

    // std::cout << x_int<<"-"<<y_int<<"-"<<z_int << "\n";
    // std::cout << x_decimal<<"-"<<y_decimal<<"-"<<z_decimal << "\n";
    // std::cout << x_fade<<"-"<<y_fade<<"-"<<z_fade << "\n";

    //these vars mean vertex hash (x,y,z) ex: vh_000 vertex hash(0,0,0)
    int vh_000{0}, vh_001{0}, vh_010{0}, vh_011{0}, vh_100{0}, vh_101{0}, vh_110{0}, vh_111{0};

    vh_000 = m_permutations[ m_permutations[ m_permutations[x_int] + y_int ] + z_int ];
    vh_010 = m_permutations[ m_permutations[ m_permutations[x_int] + y_int + 1 ] + z_int ];
    vh_001 = m_permutations[ m_permutations[ m_permutations[x_int] + y_int ] + z_int + 1 ];
    vh_011 = m_permutations[ m_permutations[ m_permutations[x_int] + y_int + 1 ] + z_int + 1 ];//max index will be 255+255+1 = 511 (last valid index)

    vh_100 = m_permutations[ m_permutations[ m_permutations[x_int + 1] + y_int ] + z_int ];
    vh_110 = m_permutations[ m_permutations[ m_permutations[x_int + 1] + y_int + 1 ] + z_int ];
    vh_101 = m_permutations[ m_permutations[ m_permutations[x_int + 1] + y_int ] + z_int + 1 ];
    vh_111 = m_permutations[ m_permutations[ m_permutations[x_int + 1] + y_int + 1 ] + z_int + 1 ];//max index will be 255+255+1 = 511 (last valid index)

    // std::cout << vh_000<<"-"<<vh_010<<"-"<<vh_001 <<"-"<<vh_011<< "\n";
    // std::cout << vh_100<<"-"<<vh_110<<"-"<<vh_101 <<"-"<<vh_111<< "\n";

    // std::cout << m_permutations[x_int]<<"\n";
    //interpolate x values
    //the x coordinate from the previous vh_xxx vars will be removed
    //so x_00 is the interpolation of vh_000 and vh_100
    double x_00{0}, x_01{0}, x_10{0}, x_11{0};

    x_00 = this->Lerp( this->Gradient(vh_000, x_decimal, y_decimal, z_decimal), this->Gradient(vh_100, x_decimal, y_decimal, z_decimal), x_fade);
    x_01 = this->Lerp( this->Gradient(vh_001, x_decimal, y_decimal, z_decimal), this->Gradient(vh_101, x_decimal, y_decimal, z_decimal), x_fade);
    x_10 = this->Lerp( this->Gradient(vh_010, x_decimal, y_decimal, z_decimal), this->Gradient(vh_110, x_decimal, y_decimal, z_decimal), x_fade);
    x_11 = this->Lerp( this->Gradient(vh_011, x_decimal, y_decimal, z_decimal), this->Gradient(vh_111, x_decimal, y_decimal, z_decimal), x_fade);

    // std::cout << x_00<<"-"<<x_01<<"-"<<x_10 <<"-"<<x_11<< "\n";
    //interpolate y values, based on the result from x interpolations
    //the x coordinate from the previous x_xx vars will be removed. NOTE: the x of x_00 is the y from vh_000
    //so y_0 is the interpolation of x_00 and x_10
    double y_0{0}, y_1{0};
    y_0 = this->Lerp(x_00, x_01, y_fade);
    y_1 = this->Lerp(x_10, x_11, y_fade);

    //return the interpolation of z
    return this->Lerp(y_0, y_1, z_fade);
}

double PerlinNoise::OctaveNoise(double x, double y, double z, int total_octaves, double persistence)
{
    double noise{0};
    double frequency{1};
    double amplitude{1};
    double sum_amplitude{0};

    for(int i{0}; i < total_octaves; ++i)
    {
        noise = this->Noise(x * frequency, y * frequency, z * frequency) * amplitude;
        noise = (noise + 1)/2;
        sum_amplitude += amplitude;

        frequency *= persistence; //Update frequency
        amplitude *= 2; //Update amplitude
    }
    return noise / sum_amplitude;

    // double total = 0;
    // double frequency = 1;
    // double amplitude = 1;
    // double maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
    // for(int i{0}; i < total_octaves; ++i)
    // {
    //     total += this->Noise(x * frequency, y * frequency, z * frequency) * amplitude;
    //
    //     maxValue += amplitude;
    //
    //     amplitude *= persistence;
    //     frequency *= 2;
    // }
    //
    // return total/maxValue;
}

double PerlinNoise::Fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10); // 6t^5 - 15t^4 + 10t^3
}

double PerlinNoise::Gradient(int hash, double x, double y, double z)
{
    //if we run the original gradient function from Ken Perlin's paper,
    //we get 16 different combinations for the variable pair u,v (some are the same but the values are switched u,v -> v,u)
    //therefore we can inprove its performance with the following switch that contains all 16 different cases

    switch(hash & 15)//from 0 to 15
    {
        case 0:  return  x + y;
        case 1:  return -x + y;
        case 2:  return  x - y;
        case 3:  return -x - y;
        case 4:  return  x + z;
        case 5:  return -x + z;
        case 6:  return  x - z;
        case 7:  return -x - z;
        case 8:  return  y + z;
        case 9:  return -y + z;
        case 10: return  y - z;
        case 11: return -y - z;
        case 12: return  y + x;
        case 13: return -y + z;
        case 14: return  y - x;
        case 15: return -y - z;
        default: return 0; // never happens
    }
}

void PerlinNoise::GeneratePermutationVector()
{
    m_permutations.clear();
    m_permutations.resize(256);
    std::iota(m_permutations.begin(), m_permutations.end(), 0);

    //double permutation vector size
    m_permutations.insert(m_permutations.begin(), m_permutations.begin(), m_permutations.end());

    std::default_random_engine engine(m_seed);
    std::shuffle(m_permutations.begin(), m_permutations.end(), engine);
}

double PerlinNoise::Lerp(const double& start, const double& end, const double& t)
{
    return (1-t) * start + t * end;
    //return start + (end - start) * t;//damn precision errors
}
