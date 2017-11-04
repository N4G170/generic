#include "random.hpp"

std::default_random_engine& RandomEngine()
{
    static std::default_random_engine engine{};
    return engine;
}

void GenerateNewSeed()
{
    static std::random_device device{};
    RandomEngine().seed( device() );
}


int Random(int min, int max)
{
    // if(min > max)
    //     std::swap(min,max);
    GenerateNewSeed();
    static std::uniform_int_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}

int Random(int min, int max, uint32_t seed)
{
    // if(min > max)
    //     std::swap(min,max);
    RandomEngine().seed( seed );
    static std::uniform_int_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}

float Random(float min, float max)
{
    // if(min > max)
    //     std::swap(min,max);
    GenerateNewSeed();
    static std::uniform_real_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}

float Random(float min, float max, uint32_t seed)
{
    // if(min > max)
    //     std::swap(min,max);
    RandomEngine().seed( seed );
    static std::uniform_real_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}

double Random(double min, double max)
{
    // if(min > max)
    //     std::swap(min,max);
    GenerateNewSeed();
    static std::uniform_real_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}

double Random(double min, double max, uint32_t seed)
{
    // if(min > max)
    //     std::swap(min,max);
    RandomEngine().seed( seed );
    static std::uniform_real_distribution<>  distribution{};
    using  param_t  = decltype(distribution)::param_type;

    return distribution( RandomEngine(), param_t{min, max} );
}
