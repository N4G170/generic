#include "snake_game.hpp"
#include "random.hpp"
#include <iostream>

SnakeGame::SnakeGame(StateMachine* state_machine, const std::string& state_name, SystemManager* system_manager_ptr):
    StateInterface(state_machine, state_name, system_manager_ptr)
{
    int centre = snake_grid_size/2;
    m_snake.push_back({centre, centre});
    m_time_to_move = 0;
    m_paused = false;

    m_snake_direction = Direction::RIGHT;
    m_snake_cell.w = m_snake_cell.h = cell_size;Point m_snake_head;
    m_snake_cell.x = m_snake_cell.y = cell_size*centre;

    m_offset_x = window_width/2 - snake_grid_size/2 * cell_size;
    m_offset_y = window_height/2 - snake_grid_size/2 * cell_size;

    ResetGame();

    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "'R' - Reset game (and score)", Colour::Magenta, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "'ESC' - Back to menu", Colour::Magenta, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "Score: ", Colour::Magenta, 15, 15, -1, -1));
    // m_labels.push_back(new sdl_gui::Label(renderer, "data/font/DejaVuSansMono.ttf", 16, "Arrow keys to change direction.", Colour::Magenta, 15, 15, -1, -1));
}

SnakeGame::~SnakeGame()
{

}

void SnakeGame::Input(const SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE: m_state_machine_ptr->ChangeState(StateName::Menu); break;

            case SDLK_UP: if(m_snake_direction != Direction::DOWN && !m_paused) m_snake_direction = Direction::UP;   break;
            case SDLK_DOWN: if(m_snake_direction != Direction::UP && !m_paused) m_snake_direction = Direction::DOWN;   break;
            case SDLK_LEFT: if(m_snake_direction != Direction::RIGHT && !m_paused) m_snake_direction = Direction::LEFT;   break;
            case SDLK_RIGHT: if(m_snake_direction != Direction::LEFT && !m_paused) m_snake_direction = Direction::RIGHT;   break;

            case SDLK_p:  m_paused = !m_paused; break;
            case SDLK_r:  ResetGame(); break;

        }
    }
}

void SnakeGame::Logic(float delta_time)
{
    if(m_paused) return;
    //SDL_Delay(1000);
    m_time_to_move += delta_time;

    if(m_time_to_move > 0.1)
    {
        bool dead {false};
        Point new_snake_pos = m_snake[0];
        m_time_to_move = 0;

        switch (m_snake_direction)
        {
            case Direction::DOWN : ++(new_snake_pos.second); break;
            case Direction::UP :  --(new_snake_pos.second); break;
            case Direction::RIGHT : ++(new_snake_pos.first); break;
            case Direction::LEFT : --(new_snake_pos.first); break;
        }

        if(m_grid[m_snake[0].first][m_snake[0].second] == 2)//enumerate
        {
            m_snake.push_back({m_snake[m_snake.size() - 1].first, m_snake[m_snake.size() - 1].second});
            //m_grid[m_snake[0].first][m_snake[0].second] = 1;
            CreateFood();
            //std::cout << m_snake.size() << "\n";
        }
        //update body
        for(unsigned int i(m_snake.size() - 1); i > 0; --i)
        {
            m_grid[m_snake[i].first][m_snake[i].second] = 0;
            m_snake[i].first = m_snake[i-1].first;
            m_snake[i].second = m_snake[i-1].second;
            //m_grid[m_snake[i].first][m_snake[i].second] = 1;
        }
        for(unsigned int i{1}; i < m_snake.size(); ++i)
        {
            m_grid[m_snake[i].first][m_snake[i].second] = 1;
        }
        m_snake[0] = new_snake_pos;

        //check move grid limits
        if(new_snake_pos.first >= snake_grid_size) dead = true;
        else if(new_snake_pos.first < 0) dead = true;
        if(new_snake_pos.second >= snake_grid_size) dead = true;
        else if(new_snake_pos.second < 0) dead = true;

        if(m_grid[m_snake[0].first][m_snake[0].second] == 1) {dead = true; std::cout << "asd" << "\n";}

        if(dead)
        {
            ResetGame();
        }
    }
}

void SnakeGame::Render(SDL_Renderer* renderer, float delta_time)
{
    SDL_SetRenderDrawColor( renderer, Colour::Black.r, Colour::Black.g, Colour::Black.b, Colour::Black.a );
    SDL_RenderClear( renderer );

    SDL_SetRenderDrawColor( renderer, Colour::Cyan.r, Colour::Cyan.g, Colour::Cyan.b, Colour::Cyan.a );
    for(int i{0}; i < snake_grid_size; ++i)
    {
        for(int j{0}; j < snake_grid_size; ++j)
        {
            if(m_grid[i][j] == 1)
            {
                //std::cout << i<<" - "<<j << "\n";
                SDL_Rect a { cell_size * i + m_offset_x, cell_size * j + m_offset_y, cell_size, cell_size };
                SDL_RenderFillRect(renderer, &a);
            }
        }
    }
    //std::cout << "---------------" << "\n";

    SDL_SetRenderDrawColor( renderer, Colour::Green.r, Colour::Green.g, Colour::Green.b, Colour::Green.a );

    //render Snake head
    m_snake_cell.x = cell_size * m_snake[0].first + m_offset_x;
    m_snake_cell.y = cell_size * m_snake[0].second + m_offset_y;
    SDL_RenderDrawRect(renderer, &m_snake_cell);

    //tail
    SDL_SetRenderDrawColor( renderer, Colour::White.r, Colour::White.g, Colour::White.b, Colour::White.a );
    for(unsigned int i{1}; i < m_snake.size(); ++i)
    {
        m_snake_cell.x = cell_size * m_snake[i].first + m_offset_x;
        m_snake_cell.y = cell_size * m_snake[i].second + m_offset_y;
        SDL_RenderDrawRect(renderer, &m_snake_cell);
    }

    SDL_Rect r {m_offset_x - 1, m_offset_y - 1, snake_grid_size*cell_size + 1, snake_grid_size*cell_size + 1};
    SDL_RenderDrawRect(renderer, &r);

    //render food
    SDL_SetRenderDrawColor( renderer, Colour::Red.r, Colour::Red.g, Colour::Red.b, Colour::Red.a );
    //reuse snake_cell
    m_snake_cell.x = cell_size * m_food_position.first + m_offset_x;
    m_snake_cell.y = cell_size * m_food_position.second + m_offset_y;
    SDL_RenderDrawRect(renderer, &m_snake_cell);

}

void SnakeGame::CreateFood()
{
    do
    {
        m_food_position.first = Random(0, snake_grid_size - 1);//x
        m_food_position.second = Random(0, snake_grid_size - 1);//y
    }
    while(m_grid[m_food_position.first][m_food_position.second] > 0);
    m_grid[m_food_position.first][m_food_position.second] = 2;
}

void SnakeGame::ResetGame()
{
    if(m_snake.size() > 1)//more than head
        m_snake.erase(++m_snake.begin(), m_snake.end());

    m_snake[0].first = m_snake[0].second = snake_grid_size/2;

    //clear grid
    for(int i{0}; i < snake_grid_size; ++i)
        for(int j{0}; j < snake_grid_size; ++j)
            m_grid[i][j] = 0;

    CreateFood();
}
