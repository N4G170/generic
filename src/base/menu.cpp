#include "menu.hpp"
#include "constants.hpp"
#include <iostream>

Menu::Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, TTF_Font* font):StateInterface(state_machine, state_name)
{
    int btn_h{25};
    int offset{15};
    m_buttons.push_back(new sdl_gui::Button(renderer, {15, (btn_h + 2)*0 + offset}, {100, btn_h}));
    // m_buttons.push_back(new sdl_gui::Button(renderer, {15, (btn_h + 2)*1 + offset}, {100, btn_h}));
    // m_buttons.push_back(new sdl_gui::Button(renderer, {15, (btn_h + 2)*2 + offset}, {100, btn_h}));
    // m_buttons.push_back(new sdl_gui::Button(renderer, {15, (btn_h + 2)*3 + offset}, {100, btn_h}));
    // m_buttons.push_back(new sdl_gui::Button(renderer, {15, (btn_h + 2)*4 + offset}, {100, btn_h}));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "<b>1</b> - A* Grid Map", Colour::Black, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "<b>2</b> - Rain demo", Colour::Black, 15, 30, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "<b>3</b> - Snake Game demo", Colour::Black, 15, 45, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "<b>4</b> - Solar System demo", Colour::Black, 15, 60, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "<b>5</b> - Influence Wars", Colour::Black, 15, 75, -1, -1));

    // SDL_Surface *sshot = SDL_CreateRGBSurface(0, 1280, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    // SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    // SDL_SaveBMP(sshot, "screenshot.bmp");
    // SDL_FreeSurface(sshot);
}

Menu::~Menu()
{
    for(sdl_gui::Button* button : m_buttons)
        delete(button);
    m_buttons.clear();
}

void Menu::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: *m_state_machine_ptr->m_quit_flag = true; break;
            case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Map_Demo); break;
            case SDLK_2: m_state_machine_ptr->ChangeState(StateName::Rain); break;
            case SDLK_3: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            case SDLK_4: m_state_machine_ptr->ChangeState(StateName::Solar_System); break;
            case SDLK_5: m_state_machine_ptr->ChangeState(StateName::Influence_Wars); break;
        }
    }

    for(sdl_gui::Button* button : m_buttons)
    {
        button->Input(event);
    }
}

void Menu::Logic(float delta_time)
{
    for(sdl_gui::Button* button : m_buttons)
    {
        button->Logic();
    }
}

void Menu::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_SetRenderDrawColor( renderer, Colour::Grey.r, Colour::Grey.g, Colour::Grey.b, Colour::Grey.a );
    SDL_RenderClear( renderer );

    // SDL_SetRenderDrawColor( renderer, Colour::Storm_Petrel.r, Colour::Storm_Petrel.g, Colour::Storm_Petrel.b, 128);
    SDL_SetRenderDrawColor( renderer, 255,255,255,255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect aux_rect{10,10,200,100};
    SDL_RenderFillRect(renderer, &aux_rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    for(sdl_gui::Button* button : m_buttons)
        button->Render();

}
