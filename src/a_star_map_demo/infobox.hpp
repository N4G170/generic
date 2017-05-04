#ifndef INFOBOX_HPP
#define INFOBOX_HPP

#include <map>
// #include <initializer_list>
#include "object.hpp"
#include "label.hpp"
#include "constants.hpp"

// struct LabelInitData
// {
//     std::string name;
//     float x;
//     float y;
//     SDL_Colour colours;
// };

class Infobox: public Object
{
    public:
        Infobox();
        virtual ~Infobox();
        /**
         * Configure the position of the infobox.
         */
        void Config(Transform* parent, const float& local_x, const float& local_y, const int& width, const int& height);
        void ShowBG(bool show_bg);
        void SetBgColour(SDL_Colour bg_colour = Colour::Grey, bool apply_alpha = false, bool show_bg = true);

        void Input(const SDL_Event& event);
        void Logic(float fixed_frame_time);
        void Render(SDL_Renderer *renderer, float delta_time);

        // void CreateLabels(std::initializer_list<LabelInitData> labels_data);
        // void CreateLabel(LabelInitData label_data);
        void CreateLabel(const int id, SDL_Renderer* renderer, TTF_Font* font, float local_x, float local_y, std::string text, SDL_Colour colour);
        void ChangeText(const int id, const std::string& new_text);
        void ChangeColour(const int id, SDL_Colour new_colour);

    private:
        //bg
        SDL_Colour m_bg_colour;
        bool m_show_bg;
        bool m_apply_bg_alpha;

        std::map<int, sdl_gui::Label> m_labels;
        inline bool LabelExists(const int id);
        /**
         * Updates the global positions of the labels. Called when infobox position is updated
         */
        void UpdateLabelPositions();
};

#endif //INFOBOX_HPP
