// #include "infobox.hpp"
//
// Infobox::Infobox():m_show_bg{true}, m_apply_bg_alpha{false}
// {
//
// }
//
// Infobox::~Infobox()
// {
//
// }
//
// void Infobox::Config(Transform* parent, const float& local_x, const float& local_y, const int& width, const int& height)
// {
//     m_transform.SetParent(parent);
//     m_transform.Position(local_x, local_y);
//     m_transform.Width(width);
//     m_transform.Height(height);
//
//     m_transform.UpdateSDLRects();
//
//     // for(auto& label : m_labels)
//     //     label.second.SetPositionOffset( m_transform.GetGlobalSDLRect().x, m_transform.GetGlobalSDLRect().y );
// }
//
// void Infobox::ShowBG(bool show_bg)
// {
//     m_show_bg = show_bg;
// }
//
// void Infobox::SetBgColour(SDL_Colour bg_colour, bool apply_alpha, bool show_bg)
// {
//     m_bg_colour = bg_colour;
//     m_apply_bg_alpha = apply_alpha;
//     m_show_bg = show_bg;
// }
//
// void Infobox::Input(const SDL_Event& event)
// {
//
// }
//
// void Infobox::Logic(float fixed_frame_time)
// {
//
// }
//
// void Infobox::Render(SDL_Renderer *renderer, float delta_time)
// {
//     SDL_SetRenderDrawColor( renderer, m_bg_colour.r, m_bg_colour.g, m_bg_colour.b, m_bg_colour.a);
//     if(m_apply_bg_alpha)
//     {
//         SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//         SDL_RenderFillRect(renderer, m_transform.GetGlobalSDLRectPtr());
//         SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
//     }
//     else
//     {
//         SDL_RenderFillRect(renderer, m_transform.GetGlobalSDLRectPtr());
//     }
//
//     // for(auto& label : m_labels)
//     //     label.second.Render(renderer);
// }
//
//
// void Infobox::CreateLabel(const int id, SDL_Renderer* renderer, TTF_Font* font, float local_x, float local_y, std::string text, SDL_Colour colour)
// {
//     m_transform.UpdateSDLRects();
//     local_x += m_transform.GlobalPosition().X();
//     local_y += m_transform.GlobalPosition().Y();
//     // m_labels[id].ConfigLabel(renderer, font, local_x, local_y, text, colour);
// }
//
// void Infobox::ChangeText(const int id, const std::string& new_text)
// {
//     // if(LabelExists(id))
//     //     m_labels[id].SetString(new_text);
// }
//
// void Infobox::ChangeColour(const int id, SDL_Color new_colour)
// {
//     // if(LabelExists(id))
//     //     m_labels[id].ChangeColour(new_colour);
// }
//
// bool Infobox::LabelExists(const int id)
// {
//     return m_labels.find(id) != m_labels.end();
// }
//
// void Infobox::UpdateLabelPositions()
// {
//     m_transform.UpdateSDLRects();
//     // for(auto& label : m_labels)
//     //     label.second.SetPositionOffset( m_transform.GetGlobalSDLRect().x, m_transform.GetGlobalSDLRect().y );
// }
