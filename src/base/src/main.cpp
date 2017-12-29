#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <system_error>
#include <memory>
#include <chrono>

#include "state_machine.hpp"
#include "constants.hpp"

#include "system_manager.hpp"
#include "shapes.hpp"
#include "deleters.hpp"

// <f> SDL init/terminate
bool InitSDL(std::unique_ptr<SDL_Window, SDLDeleters>& window, std::unique_ptr<SDL_Renderer, SDLDeleters>& renderer)
{
    //Initialize SDL
    int result = SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO );
    if( result < 0 )
    {
        std::cout<<"SDL could not initialize! SDL_Error: "<<SDL_GetError()<<std::endl;

        return false;
    }
    else
    {
        //Create window
        SDL_Window* window_ptr = SDL_CreateWindow( window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_SHOWN );
        if( window_ptr == nullptr )
        {
            std::cout<<"Window could not be created! SDL_Error: "<<SDL_GetError()<<std::endl;

            return false;
        }
        else
        {
            window.reset(window_ptr);
            window_ptr = nullptr;
            //Create renderer for window
            SDL_Renderer* screen_renderer_ptr = SDL_CreateRenderer( window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );

            if( screen_renderer_ptr == nullptr )
            {
                std::cout<<"Renderer could not be created! SDL Error: "<<SDL_GetError()<<std::endl;

                return false;
            }
            else
            {
                renderer.reset(screen_renderer_ptr);
                screen_renderer_ptr = nullptr;

                //Initialize renderer color
                //SDL_SetRenderDrawColor( renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );
                //SDL_SetRenderDrawColor( renderer.get(), 0x00, 0x00, 0x00, 0x00 );
                SDL_SetRenderDrawColor( renderer.get(), 0x35, 0x35, 0x35, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    std::cout<<"SDL_image could not initialize! SDL_image Error: "<<IMG_GetError()<<std::endl;

                    return false;
                }
                else//init fonts
                {
                    //Initialize SDL_ttf
                    if( TTF_Init() == -1 )
                    {
                       std::cout<<"SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError()<<std::endl;
                       return false;
                    }
                    else
                    {
                        //Initialize SDL_mixer - 44100 standard frequency(CD), 2 channels (stereo)
                        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                        {
                            std::cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError()<<std::endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

void TerminateSDL(std::unique_ptr<SDL_Window, SDLDeleters>& window, std::unique_ptr<SDL_Renderer, SDLDeleters>& renderer)
{
    //keep this order
    renderer.reset( nullptr );
    window.reset( nullptr );

    //Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


// </f>

// <f> MAIN
int main(int argc, char *argv[])
{
    std::unique_ptr<SDL_Window, SDLDeleters> window;
    std::unique_ptr<SDL_Renderer, SDLDeleters> renderer;

    //init SDL subsystems
    bool init_result = InitSDL(window, renderer);

    if(!init_result)
    {
        //failed to initialize sdl

        //terminate any initialized sdl subsystems
        TerminateSDL(window, renderer);

        return -2;
    }
    else
    {
        SystemManager system_manager{window.get(), renderer.get()};

        bool quit{false};
        //initializes the first state that will run
        StateMachine state_machine {&system_manager, &quit};
        state_machine.ChangeState(StateName::Menu);

        //Create Event handler
        SDL_Event event;
        float frame_cap {1.f / 60 * 1000};
        float last_frame_time {0};

        float fixed_frame_time {0.03f};
        float accumulated_time {0};

        //main loop
        while(!quit)
        {
            auto start_time(std::chrono::high_resolution_clock::now());
            float fps{0};

            accumulated_time += last_frame_time;

            //Handle events on queue
            while( SDL_PollEvent( &event ) != 0 )
            {

                // SDL_Texture* f1 = SDL_CreateTextureFromSurface(renderer.get(), TTF_RenderText_Blended(f, std::u32string("Ups \u00c0 tester"), {255,255,255,255}));

                //TODO:0 send exit code to states
                //User requests quit
                if( event.type == SDL_QUIT)
                    quit = true;
                else if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym)
                    {

                    }
                }

                system_manager.Input(event);
                state_machine.Input(event);
            }

            //Fixed time step Logic
            while(accumulated_time >= fixed_frame_time)
            {
                system_manager.FixedLogic(fixed_frame_time);
                state_machine.FixedLogic(fixed_frame_time);
                accumulated_time -= fixed_frame_time;
            }

            //Variable time step Logic
            system_manager.Logic(last_frame_time);
            state_machine.Logic(last_frame_time);

            //Clear screen
            SDL_SetRenderDrawColor( renderer.get(), 0x00, 0x00, 0x00, 0x00 );
            SDL_RenderClear( renderer.get() );

			system_manager.Render(last_frame_time);
            state_machine.Render(last_frame_time);

			//Update screen
			SDL_RenderPresent( renderer.get() );

            //Update frame timers
            auto delta_time(std::chrono::high_resolution_clock::now() - start_time);
            float frame_time = std::chrono::duration_cast< std::chrono::duration<float, std::milli> >(delta_time).count();

            //fps cap
            if(frame_time < frame_cap)
            {
                SDL_Delay(frame_cap - frame_time);
                frame_time = frame_cap;
            }
            frame_time /= 1000.f;
            fps = 1.f / frame_time;

            last_frame_time = frame_time;

            SDL_SetWindowTitle(window.get(), ( window_name +" - "+ std::to_string(fps)+" FPS").c_str() );

            //run destroy check
            system_manager.DestroyElements();

        }//while(!quit)
    }

    //Terminate SDL and clear "global" pointers
    TerminateSDL(window, renderer);

    return 0;
}
// </f>
