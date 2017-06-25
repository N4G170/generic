#include "menu.hpp"
#include "constants.hpp"
#include "sdl_gui_log.hpp"
#include "sdl_gui_constants.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_checkbox_group.hpp"
#include "sdl_gui_progress_bar.hpp"
#include "sdl_gui_slider.hpp"
#include "sdl_gui_label.hpp"
#include "sdl_gui_textbox.hpp"

SDL_Colour bg{Colour::Grey};
sdl_gui::CheckBoxGroup* checkboxgroup;
sdl_gui::ProgressBar* progress_bar_h1;
sdl_gui::ProgressBar* progress_bar_h2;
sdl_gui::ProgressBar* progress_bar_v1;
sdl_gui::ProgressBar* progress_bar_v2;

sdl_gui::Slider* slider;
sdl_gui::Textbox* textbox;

void Check(std::vector<sdl_gui::CheckBox*>& selected)
{
    std::string str = "";
    for(auto& checkbox : selected)
        str += std::to_string(checkbox->Value()) + " ";

    str +="\n";

    sdl_gui::Log(str);
}

Menu::Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr):StateInterface(state_machine, state_name,resource_manager_ptr),
    m_container_box{renderer_ptr, resource_manager_ptr, {5,5}, {250, 150}}
{
    int btn_w{200};
    int btn_h{25};
    int offset{15};
    int label_local_x{5};
    int label_local_y{4};

    sdl_gui::Button* btn = new sdl_gui::Button(renderer_ptr, resource_manager_ptr, {15, (btn_h + 2)*0 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Map_Demo));
    // btn->CreateLabel("<b>1</b> - A* Grid Map", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBorder(true);
    m_container_box.AddElement(btn, btn, btn);

    btn = new sdl_gui::Button(renderer_ptr, resource_manager_ptr, {15, (btn_h + 2)*1 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Rain));
    // btn->CreateLabel("<b>2</b> - Rain demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBorder(true);
    m_container_box.AddElement(btn, btn, btn);

    btn = new sdl_gui::Button(renderer_ptr, resource_manager_ptr, {15, (btn_h + 2)*2 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Snake));
    // btn->CreateLabel("<b>3</b> - Snake Game demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBorder(true);
    m_container_box.AddElement(btn, btn, btn);

    btn = new sdl_gui::Button(renderer_ptr, resource_manager_ptr, {15, (btn_h + 2)*3 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Solar_System));
    // btn->CreateLabel("<b>4</b> - Solar System demo", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBorder(true);
    m_container_box.AddElement(btn, btn, btn);

    btn = new sdl_gui::Button(renderer_ptr, resource_manager_ptr, {15, (btn_h + 2)*4 + offset}, {btn_w, btn_h});
    btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseCallback(sdl_gui::MouseCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Influence_Wars));
    // btn->CreateLabel("<b>5</b> - Influence Wars", sdl_gui::c_default_font, 15, Colour::Black, {label_local_x,label_local_y});
    // m_buttons.push_back(std::unique_ptr<sdl_gui::Button>(btn));
    btn->RenderBorder(true);
    m_container_box.AddElement(btn, btn, btn);

    btn = nullptr;

    checkboxgroup = new sdl_gui::CheckBoxGroup(renderer_ptr, resource_manager_ptr, {50,450}, {250,250});


    checkboxgroup->AddCheckBox(new sdl_gui::CheckBox(renderer_ptr, resource_manager_ptr,  {500,500}, {15,15}, 1));
    checkboxgroup->AddCheckBox(new sdl_gui::CheckBox(renderer_ptr, resource_manager_ptr,  {500,520}, {15,15}, 2));
    checkboxgroup->AddCheckBox(new sdl_gui::CheckBox(renderer_ptr, resource_manager_ptr,  {500,540}, {15,15}, 3));
    checkboxgroup->AddCheckBox(new sdl_gui::CheckBox(renderer_ptr, resource_manager_ptr,  {500,560}, {15,15}, 4));

    checkboxgroup->ValuesChanged = std::bind(&Check, std::placeholders::_1);

    progress_bar_h1 = new sdl_gui::ProgressBar(renderer_ptr, resource_manager_ptr, {500,50}, {200,25});
    progress_bar_h1->BarDirection(sdl_gui::ProgressBarDirection::RIGHT);
    progress_bar_h2 = new sdl_gui::ProgressBar(renderer_ptr, resource_manager_ptr, {500,80}, {200,25});
    progress_bar_h2->BarDirection(sdl_gui::ProgressBarDirection::LEFT);

    progress_bar_v1 = new sdl_gui::ProgressBar(renderer_ptr, resource_manager_ptr, {710,50}, {25,200});
    progress_bar_v1->BarDirection(sdl_gui::ProgressBarDirection::UP);
    progress_bar_v2 = new sdl_gui::ProgressBar(renderer_ptr, resource_manager_ptr, {740,50}, {25,200});
    progress_bar_v2->BarDirection(sdl_gui::ProgressBarDirection::DOWN);

    slider = new sdl_gui::Slider(renderer_ptr, resource_manager_ptr, {350,350}, {200,50});

    textbox = new sdl_gui::Textbox(renderer_ptr, resource_manager_ptr, {50,300}, {200,50});
}

Menu::~Menu()
{

}

void Menu::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        // sdl_gui::Position p = m_container_box.TransformPtr()->GlobalPosition();///////////////////
        sdl_gui::Position p = textbox->TransformPtr()->GlobalPosition();///////////////////

        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: *m_state_machine_ptr->m_quit_flag = true; break;
            // case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Map_Demo); break;
            // case SDLK_2: m_state_machine_ptr->ChangeState(StateName::Rain); break;
            // case SDLK_3: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            // case SDLK_4: m_state_machine_ptr->ChangeState(StateName::Solar_System); break;
            // case SDLK_5: m_state_machine_ptr->ChangeState(StateName::Influence_Wars); break;

            case SDLK_LEFT: p.x -= 1; textbox->TransformPtr()->GlobalPosition(p); break;
            case SDLK_RIGHT: p.x += 1; textbox->TransformPtr()->GlobalPosition(p); break;
            case SDLK_UP: p.y -= 1; textbox->TransformPtr()->GlobalPosition(p); break;
            case SDLK_DOWN: p.y += 1; textbox->TransformPtr()->GlobalPosition(p); break;
            // case SDLK_LEFT: p.x -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_RIGHT: p.x += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_UP: p.y -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_DOWN: p.y += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
        }
    }

    m_container_box.Input(event);

    checkboxgroup->Input(event);

    slider->Input(event);
}

bool u{false};
float t{0};

void Menu::Logic(float delta_time)
{
    m_container_box.Logic(delta_time);

    checkboxgroup->Logic(delta_time);

    slider->Logic(delta_time);

    //ProgressBar demo
    t += delta_time;

    if(t >= 0.2)
    {
        float value = progress_bar_h1->Value();

        if(u)
        {
            if(progress_bar_h1->Value() >= progress_bar_h1->MaxValue())
            {
                value = progress_bar_h1->MaxValue();
                u = !u;
            }
            else
                ++value;
        }
        else
        {
            if(progress_bar_h1->Value() <= progress_bar_h1->MinValue())
            {
                value = progress_bar_h1->MinValue();
                u = !u;
            }
            else
                --value;
        }


        progress_bar_h1->Value(value);
        progress_bar_h2->Value(value);
        progress_bar_v1->Value(value);
        progress_bar_v2->Value(value);
    }//progressBar demo

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

    m_container_box.Render(delta_time);

    checkboxgroup->Render(delta_time);

    progress_bar_h1->Render(delta_time);
    progress_bar_h2->Render(delta_time);
    progress_bar_v1->Render(delta_time);
    progress_bar_v2->Render(delta_time);

    slider->Render(delta_time);

    textbox->Render(delta_time);
}

void Menu::ChangeStateCallback(const std::string &state)
{
    m_state_machine_ptr->ChangeState(state);
}
