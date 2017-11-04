#ifndef DEBUG_RENDER_HPP
#define DEBUG_RENDER_HPP

#include <vector>
#include "SDL.h"
#include "vector3.hpp"
#include "vector3_utils.hpp"
#include <cmath>
#include <functional>
#include <mutex>
// #include <iostream>
#include <algorithm>

struct RenderQueueEntry
{
    int z_index{0};
    std::function<void()> call;
};

class DebugRender
{
    public:
        //<f> Instance
        static DebugRender* Instance();
        static void Init(SDL_Renderer* renderer);
        //</f> /Instance
        //<f> Constructors & operator=
        /** \brief Default destructor */
        virtual ~DebugRender() noexcept;
        /** \brief Copy constructor */
        DebugRender(const DebugRender& other) = delete;
        /** \brief Move constructor */
        DebugRender(DebugRender&& other) noexcept = delete;

        /** \brief Copy operator */
        DebugRender& operator= (const DebugRender& other) = delete;
        /** \brief Move operator */
        DebugRender& operator= (DebugRender&& other) noexcept = delete;
        //</f> /Constructors & operator=

        //<f> Render Funtions
        //<f> Lines
        //<f> ONE
        inline void RenderDrawLine(int x1, int y1, int x2, int y2, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawLineCall_1, this, x1, y1, x2, y2, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderDrawLine(const Vector3<T>& point_1, const Vector3<T>& point_2, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawLineCall_2<T>, this, point_1, point_2, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawLines(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawLinesCall_1, this, points, count, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderDrawLines(const std::vector<Vector3<T>>& points, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawLinesCall_2<T>, this, points, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /MULTIPLE
        //</f> /Lines

        //<f> Points
        //<f> ONE
        inline void RenderDrawPoint(int x, int y, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawPointCall_1, this, x, y, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderDrawPoint(const Vector3<T>& point, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawPointCall_2<T>, this, point, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawPoints(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawPointsCall_1, this, points, count, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderDrawPoints(const std::vector<Vector3<T>>& points, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawPointsCall_2<T>, this, points, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /MULTIPLE
        //</f> /Points

        //<f> Rects
        //<f> ONE
        inline void RenderDrawRect(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawRectCall_1, this, rect, colour);
            m_render_queue.push_back(std::move(entry));
        }
        inline void RenderDrawRect(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawRectCall_2, this, rect, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderDrawRect(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawRectCall_3<T>, this, position, size, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderDrawRects(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderDrawRectsCall_1, this, rects, count, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /MULTIPLE
        //</f> /Rects

        //<f> Fill Rects
        //<f> ONE
        inline void RenderFillRect(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderFillRectCall_1, this, rect, colour);
            m_render_queue.push_back(std::move(entry));
        }
        inline void RenderFillRect(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderFillRectCall_2, this, rect, colour);
            m_render_queue.push_back(std::move(entry));
        }
        template<typename T>
        inline void RenderFillRect(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderFillRectCall_3<T>, this, position, size, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderFillRects(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255}, int z_index = 0)
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            RenderQueueEntry entry;
            entry.z_index = z_index;
            entry.call = std::bind(&DebugRender::RenderFillRectsCall_1, this, rects, count, colour);
            m_render_queue.push_back(std::move(entry));
        }
        //</f> /MULTIPLE
        //</f> /Fill Rects
        //</f> /Render Funtions

        //<f> Queue Management
        inline void RenderQueue()
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);

            if(!std::is_sorted(std::begin(m_render_queue), std::end(m_render_queue), [](auto& lhs, auto& rhs){ return lhs.z_index > rhs.z_index; }))
                std::sort( std::begin(m_render_queue), std::end(m_render_queue), [](auto& lhs, auto& rhs){ return lhs.z_index > rhs.z_index; } );

            for(auto& entry : m_render_queue)
                entry.call();

            ClearQueueNonBlocking();//we call non blocking as we are already inside a lock_guard
        }
        /**
         * \brief Clears the render queue. Sets a lock_guard to protect access
         */
        inline void ClearQueueBlocking()
        {
            std::lock_guard<std::mutex> lock(m_queue_mutex);
            m_render_queue.clear();
        }
        /**
         * \brief Clears the render queue. DOES NOT set a lock_guard to protect access
         */
        inline void ClearQueueNonBlocking()
        {
            m_render_queue.clear();
        }
        //</f> /Queue Management

    private:
        //<f> Private Constructor
        /** \brief Default constructor */
        explicit DebugRender(SDL_Renderer* renderer);

        //</f> /Private Constructor

        static DebugRender* s_instance;

        // vars and stuff
        SDL_Renderer* m_renderer;

        std::vector<RenderQueueEntry> m_render_queue;
        std::mutex m_queue_mutex;

        //<f> Private Render Funtions
        //<f> Lines
        //<f> ONE
        inline void RenderDrawLineCall_1(int x1, int y1, int x2, int y2, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
        }
        template<typename T>
        inline void RenderDrawLineCall_2(const Vector3<T>& point_1, const Vector3<T>& point_2, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLine(m_renderer, CoordinateToInt(point_1.X()), CoordinateToInt(point_1.Y()),
                                           CoordinateToInt(point_2.X()), CoordinateToInt(point_2.Y()));
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawLinesCall_1(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawLines(m_renderer, points, count);
        }
        template<typename T>
        inline void RenderDrawLinesCall_2(const std::vector<Vector3<T>>& points, const SDL_Colour& colour = {0,0,0,255})
        {
            std::vector<SDL_Point> sdl_points{points.size()};
            for(auto i{0}; i<points.size(); ++i)
            {
                sdl_points[i] = Vector3ToSDLPoint(points[i]);
            }
            RenderDrawLinesCall_1(sdl_points.data(), sdl_points.size(), colour);
        }
        //</f> /MULTIPLE
        //</f> /Lines

        //<f> Points
        //<f> ONE
        inline void RenderDrawPointCall_1(int x, int y, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoint(m_renderer, x, y);
        }
        template<typename T>
        inline void RenderDrawPointCall_2(const Vector3<T>& point, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoint(m_renderer, CoordinateToInt(point.X()), CoordinateToInt(point.Y()));
        }
        //</f> /ONE

        //<f> MULTIPLE
        inline void RenderDrawPointsCall_1(const SDL_Point *points, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawPoints(m_renderer, points, count);
        }
        template<typename T>
        inline void RenderDrawPointsCall_2(const std::vector<Vector3<T>>& points, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            std::vector<SDL_Point> sdl_points{points.size()};
            for(auto i{0}; i<points.size(); ++i)
            {
                sdl_points[i] = Vector3ToSDLPoint(points[i]);
            }
            SDL_RenderDrawPoints(m_renderer, sdl_points.data(), sdl_points.size());
        }
        //</f> /MULTIPLE
        //</f> /Points

        //<f> Rects
        //<f> ONE
        inline void RenderDrawRectCall_1(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawRect(m_renderer, rect);
        }
        inline void RenderDrawRectCall_2(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{rect};
            SDL_RenderDrawRect(m_renderer, &dst);
        }
        template<typename T>
        inline void RenderDrawRectCall_3(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{ Vectors3ToSDLRect(position, size) };
            SDL_RenderDrawRect(m_renderer, &dst);
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderDrawRectsCall_1(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderDrawRects(m_renderer, rects, count);
        }
        //</f> /MULTIPLE
        //</f> /Rects

        //<f> Fill Rects
        //<f> ONE
        inline void RenderFillRectCall_1(const SDL_Rect *rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderFillRect(m_renderer, rect);
        }
        inline void RenderFillRectCall_2(const SDL_Rect& rect, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{rect};
            SDL_RenderFillRect(m_renderer, &dst);
        }
        template<typename T>
        inline void RenderFillRectCall_3(const Vector3<T>& position, const Vector3<T>& size, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_Rect dst{ Vectors3ToSDLRect(position, size) };
            SDL_RenderFillRect(m_renderer, &dst);
        }
        //</f> /ONE
        //<f> MULTIPLE
        inline void RenderFillRectsCall_1(const SDL_Rect *rects, int count, const SDL_Colour& colour = {0,0,0,255})
        {
            SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
            SDL_RenderFillRects(m_renderer, rects, count);
        }
        //</f> /MULTIPLE
        //</f> /Fill Rects
        //</f> /Render Funtions
};

void DebugRenderExitError();

#endif //DEBUG_RENDER_HPP
