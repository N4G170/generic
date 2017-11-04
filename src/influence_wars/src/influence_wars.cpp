#include "influence_wars.hpp"
#include <algorithm>
#include "perlin_noise.hpp"
#include "constants.hpp"
#include "random.hpp"
#include "PerlinNoise.h"

#include <iostream>
#include "SDL.h"

#include "graph.hpp"

int map_width{130};
int map_height{80};
int map_width2{50};
int map_height2{50};
int cell_width{5};
int cell_height{5};
int map_offset{50};

SDL_Surface* surface = nullptr;
SDL_Texture* texture = nullptr;
SDL_Surface* surface2 = nullptr;
SDL_Texture* texture2 = nullptr;
PerlinNoise noise_obj(15);
PerlinNoise2 noise_obj2;

int o = 1;
int p = std::pow(2,o);

void Draw(SDL_Renderer* renderer)
{
    surface = SDL_CreateRGBSurface(0, map_width, map_height, 32, 0,0,0,255);
    surface2 = SDL_CreateRGBSurface(0, map_width2, map_height2, 32, 0,0,0,255);

    double max = -10;
    double min = 10;
    double max2 = -10;
    double min2 = 10;

int e1=0; int e2=0;
PerlinNoise noise_obj_e1(Random(0,256));
    Uint32* pixels = static_cast<Uint32*>(surface->pixels);
    for(int i{0}; i < map_width*map_height; ++i)
    {
        int x = i % map_width;
        int y = i / map_width;
        // double noise = noise_obj2.noise(static_cast<double>(x) / map_width, static_cast<double>(y) / map_height,0);
        double noise{0};
        double noise2{0};
        // noise2 = (noise_obj_e1.Noise(static_cast<double>(x) / map_width, static_cast<double>(y) / map_height,0) + 1) / 2;
        // //noise_obj.Seed(Random(0,256));
        // noise += (noise_obj_e2.Noise(static_cast<double>(x) / map_width, static_cast<double>(y) / map_height,0) + 1) / 2 * 0.3;
        // noise += (noise_obj_e3.Noise(static_cast<double>(x) / map_width, static_cast<double>(y) / map_height,0) + 1) / 2 * 0.2;


        noise = (noise_obj.Noise(static_cast<double>(x) / map_width, static_cast<double>(y) / map_height, 0) + 1.732) / 3.464;
        // noise = noise_obj.OctaveNoise(static_cast<double>(x) / map_width / p + noise2, static_cast<double>(y) / map_height / p + noise2, 0, o, p);

        SDL_Colour c;
        if(noise<0){
            ++e1;
            c.r = 0, c.g = 255, c.b = 0, c.a = 255;
            std::cout << noise <<" - "<<static_cast<double>(x)<<" - "<<(static_cast<double>(x) / map_width)<<" - "<<static_cast<double>(y)<<" - "<<(static_cast<double>(y) / map_width)<< "\n";
        }
        else if(noise <= 0.1) { c.r = 110, c.g = 139, c.b = 61, c.a = 255; }//DarkOliveGreen4
        else if(noise <= 0.2) { c.r = 189, c.g = 183, c.b = 107, c.a = 255; }//DarkKhaki
        else if(noise <= 0.3) { c.r = 222, c.g = 184, c.b = 135, c.a = 255; }//burlywood
        else if(noise <= 0.4) { c.r = 139, c.g = 115, c.b = 85, c.a = 255; }//burlywood4
        else if(noise <= 0.5) { c.r = 142, c.g = 107, c.b = 35, c.a = 255; }//Sienna brown
        else if(noise <= 0.6) { c.r = 107, c.g = 66, c.b = 38, c.a = 255; }//Semi-Sweet Chocolate brown
        else if(noise <= 0.7) { c.r = 119, c.g = 119, c.b = 119, c.a = 255; }//grey
        else if(noise <= 0.8) { c.r = 85, c.g = 85, c.b = 85, c.a = 255; }//darker grey
        else if(noise <= 0.9) { c.r = 34, c.g = 34, c.b = 34, c.a = 255; }//even darker grey
        else if(noise <= 1.0) { c.r = 245, c.g = 255, c.b = 250, c.a = 255; }//MintCream
        else if(noise<1.0){
            ++e2;
            c.r = 255, c.g = 0, c.b = 0, c.a = 255;
            std::cout << noise << "\n";
        }
        c.a *= noise;

        pixels[i] = SDL_MapRGBA(surface->format, static_cast<Uint8>(c.r), static_cast<Uint8>(c.g), static_cast<Uint8>(c.b), static_cast<Uint8>(c.a));
        // pixels[i] = SDL_MapRGBA(surface->format, static_cast<Uint8>(255*noise), static_cast<Uint8>(255*noise), static_cast<Uint8>(255*noise), 255);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
}

//VORONOI
struct Data{};

InfluenceWars::InfluenceWars(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr)
{
    Draw(m_system_manager_ptr->Renderer());

    // Graph<Data> graph;
    // GraphNode<Data> node_1;
}

InfluenceWars::~InfluenceWars() noexcept
{

}

// InfluenceWars::InfluenceWars(const InfluenceWars& other): StateInterface(other)
// {
//
// }

// InfluenceWars::InfluenceWars(InfluenceWars&& other) noexcept : StateInterface(static_cast<StateInterface>(other))
// {
//
// }

InfluenceWars& InfluenceWars::operator= (const InfluenceWars& other)
{
    // if(this != &other)//not same ref?
    // {
    //     InfluenceWars tmp(other);
    //     *this = std::move(tmp);
    // }

    return *this;
}

InfluenceWars& InfluenceWars::operator= (InfluenceWars &&other) noexcept
{
    if(this != &other)
    {

    }

    return *this;
}
bool reload=false;
void InfluenceWars::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;
            case SDLK_r: reload=true; break;
            case SDLK_KP_MINUS: o = (o-1 <= 0)?1:o-1; p = std::pow(2,o); break;
            case SDLK_KP_PLUS: o = (o+1 >= 9)?8:o+1; p = std::pow(2,o); break;
        }
    }
}

void InfluenceWars::Logic(float delta_time)
{

}

void InfluenceWars::Render(SDL_Renderer* renderer, float delta_time)
{
    // for(auto& cell : m_map)
    //     cell.Render(renderer);

if(reload)
{
    reload = false;
    noise_obj.Seed(Random(0,512));
    Draw(renderer);
    std::cout << o << "\n";
}

    SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_ADD);
    SDL_Rect rect{map_offset, map_offset, map_width*10, map_height*10};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    // SDL_Rect rect2{map_width*20 + map_offset*2, map_offset, map_width2*20, map_height2*20};
    // SDL_RenderCopy(renderer, texture2, NULL, &rect2);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_NONE);
}
