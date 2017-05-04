#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <array>
#include <vector>
#include <utility>
#include "constants.hpp"
#include "state_interface.hpp"
#include "label.hpp"

using Point = std::pair<int,int>;

enum Direction{ UP, DOWN, LEFT, RIGHT };

class SnakeGame : public StateInterface
{
    public:
        SnakeGame(StateMachine* state_machine, const std::string& state_name, SDL_Renderer* renderer, TTF_Font* font);
        virtual ~SnakeGame();

        /**
         * \brief Precess SDL user input
         */
        virtual void Input(const SDL_Event&);

        /**
         * \brief Process any logic, runs after input
         */
        virtual void Logic(float delta_time = 1);

        /**
         * \brief Render the state visual elements
         */
        virtual void Render(SDL_Renderer*, float delta_time);

    private:
        std::array< std::array<short, snake_grid_size>, snake_grid_size > m_grid;
        std::vector<Point> m_snake;
        float m_time_to_move;
        Direction m_snake_direction;
        SDL_Rect m_snake_cell;

        int m_offset_x;
        int m_offset_y;

        bool m_paused;
        void ResetGame();
        void CreateFood();
        Point m_food_position;

        std::vector<sdl_gui::Label*> m_labels;
};

#endif//SNAKE_GAME_HPP
