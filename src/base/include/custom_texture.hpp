#ifndef CUSTOM_TEXTURE_HPP
#define CUSTOM_TEXTURE_HPP
#include "SDL.h"
#include <memory>

#include "deleters.hpp"
#include "texture.hpp"
#include "vector3.hpp"
#include "vector3_utils.hpp"
#include <vector>


class CustomTexture
{
    public:
        /* Default constructor */
        CustomTexture();

        /**
         * The texture will be created with TARGET texture access type and pixel format RGBA8888
         */
        CustomTexture(SDL_Renderer* renderer_ptr, int w, int h);

        CustomTexture(SDL_Renderer* renderer_ptr, const Vector3<float>& size);

        /**
         * NOTE: This class will create a copy of the texture and manage it
         * \return [description]
         */
        CustomTexture(SDL_Renderer* renderer_ptr, SDL_Texture* texture_ptr);

        /**
         * Will create a copy of the pointer
         */
        CustomTexture(SDL_Renderer* renderer_ptr, const Texture& texture);

        /* Default destructor */
        virtual ~CustomTexture() noexcept;

        /* Copy constructor */
        CustomTexture(const CustomTexture& other);
        /* Move constructor */
        CustomTexture(CustomTexture&& other) noexcept;

        /* Copy operator */
        CustomTexture& operator= (const CustomTexture& other);
        /* Move operator */
        CustomTexture& operator= (CustomTexture&& other) noexcept;

        //<f> Getters/Setters
        SDL_Rect* SourceRect() const { return m_src_rect; };
        void SourceRect(SDL_Rect src_rect);
        SDL_Rect* DestinationRect() const { return m_dst_rect; };
        void DestinationRect(SDL_Rect dst_rect);
        void ClearSourceRect();
        void ClearDestinationRect();
        SDL_Colour ColourModulation() const { return m_colour_modulation; };
        void ColourModulation(const SDL_Colour& colour);
        int AlphaModulation() const { return m_colour_modulation.a; };
        void AlphaModulation(int alpha){ m_colour_modulation.a = alpha;};

        void TexturePtr(SDL_Texture* texture);
        SDL_Texture* TexturePtr() const {return m_texture.get(); }
        //</f>

        //<f> Render Funtions
        //<f> Lines
        //<f> ONE
        inline void RenderDrawLineOnSelf(int x1, int y1, int x2, int y2, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderDrawLineOnSelf(const Vector3<T>& point_1, const Vector3<T>& point_2, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLine(m_renderer, CoordinateToInt(point_1.X()), CoordinateToInt(point_1.Y()),
                                           CoordinateToInt(point_2.X()), CoordinateToInt(point_2.Y()));
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawLinesOnSelf(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLines(m_renderer, points, count);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderDrawLinesOnSelf(const std::vector<Vector3<T>>& points, const SDL_Colour& colour = {0,0,0,255})
        {
            std::vector<SDL_Point> sdl_points{points.size()};
            for(auto i{0}; i<points.size(); ++i)
            {
                sdl_points[i] = Vector3ToSDLPoint(points[i]);
            }
            RenderDrawLinesOnSelf(sdl_points.data(), sdl_points.size(), colour);
        }
        //</f> /MULTIPLE
        //</f> /Lines

        //<f> Points
        //<f> ONE
        inline void RenderDrawPointOnSelf(int x, int y, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoint(m_renderer, x, y);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderDrawPointOnSelf(const Vector3<T>& point, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoint(m_renderer, CoordinateToInt(point.X()), CoordinateToInt(point.Y()));
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawPointsOnSelf(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoints(m_renderer, points, count);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderDrawPointsOnSelf(const std::vector<Vector3<T>>& points, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            std::vector<SDL_Point> sdl_points{points.size()};
            for(auto i{0}; i<points.size(); ++i)
            {
                sdl_points[i] = Vector3ToSDLPoint(points[i]);
            }
            SDL_RenderDrawPoints(m_renderer, sdl_points.data(), sdl_points.size());
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /MULTIPLE
        //</f> /Points

        //<f> Rects
        //<f> ONE
        inline void RenderDrawRectOnSelf(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawRect(m_renderer, rect);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        inline void RenderDrawRectOnSelf(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{rect};
            SDL_RenderDrawRect(m_renderer, &dst);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderDrawRectOnSelf(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{ Vectors3ToSDLRect(position, size) };
            SDL_RenderDrawRect(m_renderer, &dst);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderDrawRectsOnSelf(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawRects(m_renderer, rects, count);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /MULTIPLE
        //</f> /Rects

        //<f> Fill Rects
        //<f> ONE
        inline void RenderFillRectOnSelf(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderFillRect(m_renderer, rect);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        inline void RenderFillRectOnSelf(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{rect};
            SDL_RenderFillRect(m_renderer, &dst);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        template<typename T>
        inline void RenderFillRectOnSelf(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{ Vectors3ToSDLRect(position, size) };
            SDL_RenderFillRect(m_renderer, &dst);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderFillRectsOnSelf(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderTarget(m_renderer, m_texture.get());
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderFillRects(m_renderer, rects, count);
            SDL_SetRenderTarget(m_renderer, nullptr);
        }
        //</f> /MULTIPLE
        //</f> /Fill Rects
        //</f> /Render Funtions

        void Render();
        void Render(SDL_Rect* src_rect, SDL_Rect* dst_rect);
        /**
         * \brief Render the texture with rotation
         * \n if rotation_pivot is nullptr the used pivot will be the centre of the destination rect.
         * \n rotation_pivot value is local
         */
        void RenderEx(SDL_Rect* src_rect, SDL_Rect* dst_rect, double angle = 0, SDL_Point* rotation_pivot = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void Resize(int new_w, int new_h, bool scale_content = false);
        /**
         * \brief Clears the content of the texture and sets it to the given colour (defaul {255,255,255,0})
         */
        void Clear(const SDL_Colour& colour = {255,255,255,0});

    private:
        // vars and stuff
        //CustomTexture DOES NOT OWN THIS POINTER
        SDL_Renderer* m_renderer;

        std::unique_ptr<SDL_Texture, SDLDeleters> m_texture;

        SDL_Rect* m_src_rect;
        SDL_Rect* m_dst_rect;
        SDL_Colour m_colour_modulation;

        void ColourModulation(Uint8 r, Uint8 g, Uint8 b);
};

#endif //CUSTOM_TEXTURE_HPP
