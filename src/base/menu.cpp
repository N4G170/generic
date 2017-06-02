#include "menu.hpp"
#include "constants.hpp"
#include "sdl_gui_log.hpp"
#include "sdl_gui_constants.hpp"

#include "sdl_gui_checkbox.hpp"
sdl_gui::CheckBox* checkbox;

Menu::Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr):StateInterface(state_machine, state_name,resource_manager_ptr),
    m_container_box{resource_manager_ptr, renderer_ptr, {5,5}, {250, 150}}
{
    int btn_w{200};
    int btn_h{25};
    int offset{15};
    int label_local_x{5};
    int label_local_y{4};

    sdl_gui::Button* btn = new sdl_gui::Button(resource_manager_ptr, renderer_ptr, {15, (btn_h + 2)*0 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseClickCallbacks()->push_back(std::bind(&Menu::ChangeStateCallback, this, StateName::Map_Demo));
    btn->CreateLabel("<b>1</b> - A* Grid Map", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBoundsBorder(true);
    m_container_box.AddElement(btn, btn);

    btn = new sdl_gui::Button(resource_manager_ptr, renderer_ptr, {15, (btn_h + 2)*1 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseClickCallbacks()->push_back(std::bind(&Menu::ChangeStateCallback, this, StateName::Rain));
    btn->CreateLabel("<b>2</b> - Rain demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBoundsBorder(true);
    m_container_box.AddElement(btn, btn);

    btn = new sdl_gui::Button(resource_manager_ptr, renderer_ptr, {15, (btn_h + 2)*2 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseClickCallbacks()->push_back(std::bind(&Menu::ChangeStateCallback, this, StateName::Snake));
    btn->CreateLabel("<b>3</b> - Snake Game demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBoundsBorder(true);
    m_container_box.AddElement(btn, btn);

    btn = new sdl_gui::Button(resource_manager_ptr, renderer_ptr, {15, (btn_h + 2)*3 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseClickCallbacks()->push_back(std::bind(&Menu::ChangeStateCallback, this, StateName::Solar_System));
    btn->CreateLabel("<b>4</b> - Solar System demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBoundsBorder(true);
    m_container_box.AddElement(btn, btn);

    btn = new sdl_gui::Button(resource_manager_ptr, renderer_ptr, {15, (btn_h + 2)*4 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseClickCallbacks()->push_back(std::bind(&Menu::ChangeStateCallback, this, StateName::Influence_Wars));
    btn->CreateLabel("<b>5</b> - Influence Wars", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBoundsBorder(true);
    m_container_box.AddElement(btn, btn);

    btn = nullptr;
    // SDL_Surface *sshot = SDL_CreateRGBSurface(0, 1280, 800, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    // SDL_RenderReadPixels(renderer_ptr, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    // SDL_SaveBMP(sshot, "screenshot.bmp");
    // SDL_FreeSurface(sshot);

    checkbox = new sdl_gui::CheckBox(resource_manager_ptr, renderer_ptr, {500,500}, {15,15});
    checkbox->RenderBoundsBorder(true);
}

Menu::~Menu()
{
    m_buttons.clear();//the unique_ptrs will delete the buttons
}

void Menu::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        // sdl_gui::Position p = m_container_box.TransformPtr()->GlobalPosition();///////////////////

        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: *m_state_machine_ptr->m_quit_flag = true; break;
            // case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Map_Demo); break;
            // case SDLK_2: m_state_machine_ptr->ChangeState(StateName::Rain); break;
            // case SDLK_3: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            // case SDLK_4: m_state_machine_ptr->ChangeState(StateName::Solar_System); break;
            // case SDLK_5: m_state_machine_ptr->ChangeState(StateName::Influence_Wars); break;

            // case SDLK_LEFT: p.x -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_RIGHT: p.x += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_UP: p.y -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_DOWN: p.y += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
        }
    }

    // m_container_box.Input(event);

    checkbox->Input(event);
}
SDL_Colour bg{Colour::Grey};
void Menu::Logic(float fixed_delta_time)
{
    for(auto& button : m_buttons)
    {
        button->Logic(fixed_delta_time);
    }

    m_container_box.Logic(fixed_delta_time);

    checkbox->Logic(fixed_delta_time);

    if(checkbox->IsChecked())
        bg = Colour::Green;
    else
        bg = Colour::Grey;
}

void Menu::Render(SDL_Renderer* renderer, float delta_time)
{
    // SDL_SetRenderDrawColor( renderer, Colour::Grey.r, Colour::Grey.g, Colour::Grey.b, Colour::Grey.a );
    SDL_SetRenderDrawColor( renderer, bg.r, bg.g, bg.b, bg.a );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, Colour::Storm_Petrel.r, Colour::Storm_Petrel.g, Colour::Storm_Petrel.b, 128);
    // SDL_SetRenderDrawColor( renderer, 128,255,255,255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect aux_rect{10,10,200,100};
    SDL_RenderFillRect(renderer, &aux_rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    for(auto& button : m_buttons)
        button->Render(delta_time);
    m_container_box.Render(delta_time);

    checkbox->Render(delta_time);
}

void Menu::ChangeStateCallback(const std::string &state)
{
    m_state_machine_ptr->ChangeState(state);
}
