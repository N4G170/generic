#include "menu.hpp"
#include "constants.hpp"
#include "sdl_gui_log.hpp"
#include "sdl_gui_constants.hpp"
#include "sdl_gui_enums.hpp"
#include "sdl_gui_camera.hpp"
#include "sdl_gui_utils.hpp"

SDL_Colour bg{Colour::Rain_Drop_Blue};
sdl_gui::ProgressBar* progress_bar_h1;
sdl_gui::ProgressBar* progress_bar_h2;
sdl_gui::ProgressBar* progress_bar_v1;
sdl_gui::ProgressBar* progress_bar_v2;

void Check(std::vector<sdl_gui::CheckBox*>& selected)
{
    std::string str = "";
    for(auto& checkbox : selected)
        str += std::to_string(checkbox->Value()) + " ";

    str +="\n";

    sdl_gui::Log(str);
}

Menu::Menu(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer_ptr, sdl_gui::ResourceManager* resource_manager_ptr):
    StateInterface(state_machine, state_name,resource_manager_ptr), m_gui_manager{renderer_ptr, resource_manager_ptr}
{
    auto img = m_gui_manager.CreateElement<sdl_gui::Image>({800,50}, {350,350});
    img->ChangeTexture("data/img/button_base.png");
    // img->SetSourceRect({0,0,1,1});
    auto btn_texture = m_resource_manager_ptr->GetTexture("data/img/button_base.png");

    float btn_w{200};
    float btn_h{25};
    float offset{15};

    sdl_gui::Layout* layout = m_gui_manager.CreateElement<sdl_gui::Layout>({5,5}, {250, 150});
    sdl_gui::Button* btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*0 + offset}, {btn_w, btn_h});

    btn->TransitionType(sdl_gui::ButtonTransitionType::COLOUR);
    btn->TransitionColourPtr()->SetStateColour(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Map_Demo));
    btn->CreateLabel("<b>1</b> - A* Grid Map", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    btn->CentreLabel();
    layout->AddElement(btn);

    btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*1 + offset}, {btn_w, btn_h});
    btn->TransitionType(sdl_gui::ButtonTransitionType::SINGLE_IMAGE);
    btn->TransitionSingleImagePtr()->ChangeTexture("data/img/button_base.png");
    btn->TransitionSingleImagePtr()->SetStateTextureSrcRect({0,0,1,1}, {0,1,1,1}, {0,2,1,1}, {0,3,1,1});
    btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Rain));
    btn->CreateLabel("<b>2</b> - Rain demo", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    btn->CentreLabel();
    layout->AddElement(btn);

    btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*2 + offset}, {btn_w, btn_h});
    btn->TransitionType(sdl_gui::ButtonTransitionType::MULTI_IMAGE);
    btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Snake));
    btn->CreateLabel("<b>3</b> - Snake Game demo", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    btn->CentreLabel();
    layout->AddElement(btn);
    //
    // btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*3 + offset}, {btn_w, btn_h});
    // // btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    // btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Solar_System));
    // btn->CreateLabel("<b>4</b> - Solar System demo", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    // btn->CentreLabel();
    // layout->AddElement(btn);
    //
    // btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*4 + offset}, {btn_w, btn_h});
    // // btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    // btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Influence_Wars));
    // btn->CreateLabel("<b>5</b> - Influence Wars", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    // btn->CentreLabel();
    // layout->AddElement(btn);
    //
    // btn = m_gui_manager.CreateElement<sdl_gui::Button>({15, (btn_h + 2)*4 + offset}, {btn_w, btn_h});
    // // btn->SetStateColours(Colour::Cyan, Colour::Grey, Colour::Magenta, Colour::Rain_Drop_Blue);
    // btn->MouseInteractionPtr()->MouseButtonCallback(SDL_BUTTON_LEFT, sdl_gui::InputKeyCallbackType::CLICK, std::bind(&Menu::ChangeStateCallback, this, StateName::Particles));
    // btn->CreateLabel("<b>6</b> - Particles", sdl_gui::c_default_font_path, 15, Colour::Black, {0,0});
    // btn->CentreLabel();
    // layout->AddElement(btn);
    // btn->IsActive(false);

    btn = nullptr;

    auto checkboxgroup = m_gui_manager.CreateElement<sdl_gui::CheckBoxGroup>({50,450}, {250,250});


    checkboxgroup->AddCheckBox(m_gui_manager.CreateFreeElement<sdl_gui::CheckBox>({500,500}, {15,15}));
    checkboxgroup->AddCheckBox(m_gui_manager.CreateFreeElement<sdl_gui::CheckBox>({500,520}, {15,15}));
    checkboxgroup->AddCheckBox(m_gui_manager.CreateFreeElement<sdl_gui::CheckBox>({500,540}, {15,15}));
    checkboxgroup->AddCheckBox(m_gui_manager.CreateFreeElement<sdl_gui::CheckBox>({500,560}, {15,15}));

    checkboxgroup->ValuesChanged = std::bind(&Check, std::placeholders::_1);

    progress_bar_h1 = m_gui_manager.CreateElement<sdl_gui::ProgressBar>({500,50}, {200,25});
    progress_bar_h1->BarDirection(sdl_gui::ProgressBarDirection::RIGHT);
    progress_bar_h2 = m_gui_manager.CreateElement<sdl_gui::ProgressBar>({500,80}, {200,25});
    progress_bar_h2->BarDirection(sdl_gui::ProgressBarDirection::LEFT);

    progress_bar_v1 = m_gui_manager.CreateElement<sdl_gui::ProgressBar>({710,50}, {25,200});
    progress_bar_v1->BarDirection(sdl_gui::ProgressBarDirection::UP);
    progress_bar_v2 = m_gui_manager.CreateElement<sdl_gui::ProgressBar>({740,50}, {25,200});
    progress_bar_v2->BarDirection(sdl_gui::ProgressBarDirection::DOWN);

    m_gui_manager.CreateElement<sdl_gui::Slider>({350,350}, {200,25});

    m_gui_manager.CreateElement<sdl_gui::Textbox>({50,300}, {200,50});

    m_gui_manager.CreateElement<sdl_gui::Tooltip>({50,550}, {50,50});

    auto label = m_gui_manager.CreateElement<sdl_gui::Label>({800,500},{0,0});
    label->ConfigLabel(sdl_gui::c_default_font_path, sdl_gui::c_default_font_size, "Due to high maintenance cost of scripts related to the Arch Build System, we have decided to deprecate the abs tool and thus rsync as a way of obtaining PKGBUILDs.\
    \nThe asp tool, available in [extra], provides similar functionality to abs. asp export pkgname can be used as direct alternative; more information about its usage can be found in the documentation.\
    Additionally Subversion sparse checkouts, as described here, can be used to achieve a similar effect. For fetching all PKGBUILDs, the best way is cloning the svntogit mirrors.\
    While the extra/abs package has been already dropped, the rsync endpoint (rsync://rsync.archlinux.org/abs) will be disabled by the end of the month.", {0,0,0,255});
    label->LineLength(300);
    auto label2 = m_gui_manager.CreateElement<sdl_gui::Label>({1250,500},{0,0});
    label2->ConfigLabel(sdl_gui::c_default_font_path, sdl_gui::c_default_font_size, "Due to high maintenance cost of scripts related to the Arch Build System, we have decided to deprecate the abs tool and thus rsync as a way of obtaining PKGBUILDs.\
    The asp tool, available in [extra], provides similar functionality to abs. asp export pkgname can be used as direct alternative; more information about its usage can be found in the documentation.\
    Additionally Subversion sparse checkouts, as described here, can be used to achieve a similar effect. For fetching all PKGBUILDs, the best way is cloning the svntogit mirrors.\
    While the extra/abs package has been already dropped, the rsync endpoint (rsync://rsync.archlinux.org/abs) will be disabled by the end of the month.", {0,0,0,125});
    label2->LineLength(300);
}

Menu::~Menu()
{

}

void Menu::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        // sdl_gui::Position p = m_container_box.TransformPtr()->GlobalPosition();///////////////////
        // sdl_gui::Position p = textbox->TransformPtr()->GlobalPosition();///////////////////

        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: *m_state_machine_ptr->m_quit_flag = true; break;
            // case SDLK_1: m_state_machine_ptr->ChangeState(StateName::Map_Demo); break;
            // case SDLK_2: m_state_machine_ptr->ChangeState(StateName::Rain); break;
            // case SDLK_3: m_state_machine_ptr->ChangeState(StateName::Snake); break;
            // case SDLK_4: m_state_machine_ptr->ChangeState(StateName::Solar_System); break;
            // case SDLK_5: m_state_machine_ptr->ChangeState(StateName::Influence_Wars); break;

            // case SDLK_LEFT: p.x -= 1; textbox->TransformPtr()->GlobalPosition(p); break;
            // case SDLK_RIGHT: p.x += 1; textbox->TransformPtr()->GlobalPosition(p); break;
            // case SDLK_UP: p.y -= 1; textbox->TransformPtr()->GlobalPosition(p); break;
            // case SDLK_DOWN: p.y += 1; textbox->TransformPtr()->GlobalPosition(p); break;
            // case SDLK_LEFT: p.x -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_RIGHT: p.x += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_UP: p.y -= 1; m_container_box.TransformPtr()->GlobalPosition(p); break;
            // case SDLK_DOWN: p.y += 1; m_container_box.TransformPtr()->GlobalPosition(p); break;

            // case SDLK_LEFT: p.x -= 1;  break;
            // case SDLK_RIGHT: p.x += 1;  break;
            // case SDLK_UP: p.y -= 1;  break;
            // case SDLK_DOWN: p.y += 1;  break;
        }
        // camera.CameraPosition(p);
    }

    m_gui_manager.Input(event);
}

bool u{false};
float t{0};

void Menu::Logic(float delta_time)
{

    m_gui_manager.Logic(delta_time);

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
        // progress_bar_h2->Value(value);
        // progress_bar_v1->Value(value);
        // progress_bar_v2->Value(value);
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

    m_gui_manager.Render(delta_time);
}

void Menu::Enter()
{

}

void Menu::Exit()
{

}

void Menu::ChangeStateCallback(const std::string &state)
{
    m_gui_manager.ClearElementsInput();
    m_state_machine_ptr->ChangeState(state);
}
