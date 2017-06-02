#ifndef FONT_HPP
#define FONT_HPP

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "texture.hpp"

struct GlyphSurfaces
{
    SDL_Surface* normal;
    SDL_Surface* bold;
    SDL_Surface* italic;
    SDL_Surface* italic_bold;

    void FreeSurfaces()
    {
        SDL_FreeSurface(normal);
        SDL_FreeSurface(bold);
        SDL_FreeSurface(italic);
        SDL_FreeSurface(italic_bold);
    }
};

struct GlyphPositions
{
    SDL_Rect normal;
    SDL_Rect bold;
    SDL_Rect italic;
    SDL_Rect italic_bold;
};

class Font
{
    public:
        /* Default constructor */
        Font(SDL_Renderer* renderer_ptr, const std::string& font_path, int font_size = 12);
        /* Default destructor */
        virtual ~Font() noexcept;

        /* Copy constructor */
        Font(const Font& other) = delete;
        /* Move constructor */
        Font(Font&& other) noexcept;

        /* Copy operator */
        Font& operator= (const Font& other) = delete;
        /* Move operator */
        Font& operator= (Font&& other) noexcept;

        bool CharTexture(const char& character, int font_size, int origin_x, int origin_y, SDL_Colour font_colour, Texture* output_texture);
        //0 means no limit. if line_length < letter width, 1 char per line
        bool StringTexture(const std::string& text, int origin_x, int origin_y, SDL_Colour font_colour, SDL_Texture* output_texture, int line_length = 0);

        SDL_Texture* font(){return m_font_texture;};
    private:
        // vars and stuff
        SDL_Renderer* m_renderer_ptr;
        std::string m_source_path;
        TTF_Font* m_font_ptr;
        SDL_Texture* m_font_texture;
        std::map<int, GlyphPositions> m_glyphs_positions;

        //font stats
        int m_font_size;

        void CreateFontGlyphSheet();
        void RenderGlyph(SDL_Surface*& surface, int& w, int& i);

        //TODO: improve function
        /*
DOES NOT CHECK IF IS IN RANGE
         */
        bool CheckTextTag(bool is_open_tag, const std::vector<int>& letters, int start_index, int end_index, int type);
};

#endif //FONT_HPP
