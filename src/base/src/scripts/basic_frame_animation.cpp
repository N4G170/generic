#include "basic_frame_animation.hpp"
#include "constants.hpp"
#include <utility>


//<f> Constructors & operator=
BasicFrameAnimation::BasicFrameAnimation() : m_image{nullptr}, m_frames{},
    m_fps{c_default_anim_fps}, m_time_per_frame{1.f/c_default_anim_fps}, m_current_animation_time{0},
    m_current_frame_time{0}, m_current_frame{0}, m_playing{false}, m_loop{false}, m_backwards{false} {}

BasicFrameAnimation::~BasicFrameAnimation() noexcept
{

}

BasicFrameAnimation::BasicFrameAnimation(const BasicFrameAnimation& other) : m_image{other.m_image}, m_frames{other.m_frames},
    m_fps{other.m_fps}, m_time_per_frame{other.m_time_per_frame}, m_current_animation_time{other.m_current_animation_time},
    m_current_frame_time{other.m_current_frame_time}, m_current_frame{other.m_current_frame}, m_playing{other.m_playing}, m_loop{other.m_loop},
    m_backwards{other.m_backwards}
{

}

BasicFrameAnimation::BasicFrameAnimation(BasicFrameAnimation&& other) noexcept : m_image{std::move(other.m_image)}, m_frames{std::move(other.m_frames)},
    m_fps{std::move(other.m_fps)}, m_time_per_frame{std::move(other.m_time_per_frame)},
    m_current_animation_time{std::move(other.m_current_animation_time)},
    m_current_frame_time{std::move(other.m_current_frame_time)}, m_current_frame{std::move(other.m_current_frame)}, m_playing{std::move(other.m_playing)},
    m_loop{std::move(other.m_loop)}, m_backwards{std::move(other.m_backwards)} {}

BasicFrameAnimation& BasicFrameAnimation::operator=(const BasicFrameAnimation& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

BasicFrameAnimation& BasicFrameAnimation::operator=(BasicFrameAnimation&& other) noexcept
{
    if(this != &other)//not same ref
    {
        m_image = std::move(other.m_image);
        m_frames = std::move(other.m_frames);
        m_fps = std::move(other.m_fps);
        m_time_per_frame = std::move(other.m_time_per_frame);
        m_current_animation_time = std::move(other.m_current_animation_time);
        m_current_frame_time = std::move(other.m_current_frame_time);
        m_current_frame = std::move(other.m_current_frame);
        m_playing = std::move(other.m_playing);
        m_loop = std::move(other.m_loop);
        m_backwards = std::move(other.m_backwards);
    }
    return *this;
}
//</f>

//<f> Virtual Methods
Script* BasicFrameAnimation::Clone() { return new BasicFrameAnimation{*this}; }

void BasicFrameAnimation::Update(float delta_time)
{
    if(m_image == nullptr)
        return;

    if(m_playing)
    {
        m_current_frame_time += delta_time;
        m_current_animation_time += delta_time;//total time

        if(m_current_frame_time >= m_time_per_frame)//reached end of frame
        {
            m_current_frame_time = 0;//reset counter

            if(m_backwards)
            {
                --m_current_frame;//move to next frame
                if(m_current_frame <= 0)//reached end of vector, loop to first (if m_loop)
                {
                    //reset
                    m_current_frame = m_frames.size() - 1;
                    m_current_animation_time = 0;

                    if(!m_loop)//stop
                    {
                        Stop();
                        //stay at last frame
                        m_current_frame = 0;
                    }
                }
            }
            else
            {
                ++m_current_frame;//move to next frame
                if(m_current_frame >= m_frames.size())//reached end of vector, loop to first (if m_loop)
                {
                    //reset
                    m_current_frame = 0;
                    m_current_animation_time = 0;

                    if(!m_loop)//stop
                    {
                        Stop();
                        //stay at last frame
                        m_current_frame = m_frames.size() - 1;
                    }
                }
            }

            //update frame pointer
            m_image->SetImage(m_frames[m_current_frame].image_path);
            if(m_frames[m_current_frame].has_src_rect)
            {
                m_image->HasSrcRect(true);
                m_image->SrcRect(m_frames[m_current_frame].source_rect);
            }
        }
    }
}
//</f> /Virtual Methods

//<f> Getters/Setters

void BasicFrameAnimation::AddFrame(std::string file_path, bool has_src_rect, const SDL_Rect& src_rect)
{
    m_frames.push_back( BasicFrame{file_path, has_src_rect, src_rect} );
}

BasicFrame* BasicFrameAnimation::GetFrame(int frame_index)
{
    return frame_index < m_frames.size()? &m_frames[frame_index] : nullptr;
}

Image* BasicFrameAnimation::GetImage() const { return m_image; }
void BasicFrameAnimation::SetImage(Image* image)
{
    m_image = image;

    if(m_image != nullptr)
    {
        //update frame pointer
        m_image->SetImage(m_frames[m_current_frame].image_path);
        if(m_frames[m_current_frame].has_src_rect)
        {
            m_image->HasSrcRect(true);
            m_image->SrcRect(m_frames[m_current_frame].source_rect);
        }
    }
}
//</f>

//<f> Methods
void BasicFrameAnimation::Play()
{
    m_playing = true;
}

void BasicFrameAnimation::Pause()
{
    m_playing = false;
}

void BasicFrameAnimation::Stop()
{
    m_playing = false;
    m_current_frame = 0;
}
//</f>
