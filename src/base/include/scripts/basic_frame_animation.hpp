#include "behaviour_script.hpp"
#include <vector>
#include <cmath>
#include <string>
#include "structs.hpp"
#include "image.hpp"

#ifndef BASIC_FRAME_ANIMATION_HPP
#define BASIC_FRAME_ANIMATION_HPP

class BasicFrameAnimation : public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        BasicFrameAnimation();
        /** brief Default destructor */
        virtual ~BasicFrameAnimation() noexcept;

        /** brief Copy constructor */
        BasicFrameAnimation(const BasicFrameAnimation& other);
        /** brief Move constructor */
        BasicFrameAnimation(BasicFrameAnimation&& other) noexcept;

        /** brief Copy operator */
        BasicFrameAnimation& operator= (const BasicFrameAnimation& other);
        /** brief Move operator */
        BasicFrameAnimation& operator= (BasicFrameAnimation&& other) noexcept;
        //</f>

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f>

        //<f> Getters/Setters
        /**
         * \brief Set animation FPS. Value will never be < 1 (std::max(fps, 1))
         */
        void FPS(int fps) { m_fps = std::max(fps, 1); m_time_per_frame = 1.f/m_fps; }
        int FPS() const { return m_fps; }

        void IncreaseFPS(int value){ FPS(FPS() + value); }
        void DecreaseFPS(int value){ FPS(FPS() - value); }

        void AddFrame(std::string file_path, bool has_src_rect = false, const SDL_Rect& src_rect = {0,0,0,0});

        BasicFrame* GetFrame(int frame_index);

        int FrameIndex() const { return m_current_frame; }
        int TotalFrames() const { return m_frames.size(); }

        bool IsPlaying() const { return m_playing; }
        bool Loop() const { return m_loop; }
        void Loop(bool loop){ m_loop = loop; }
        bool Backwards() const { return m_backwards; }
        void Backwards(bool backwards){ m_backwards = backwards; }

        Image* GetImage() const;
        void SetImage(Image* image);
        //</f>

        //<f> Methods
        void Play();
        void Pause();
        void Stop();
        //</f>

    protected:
        /**
         * \breif The image script that will render the frame
         */
        Image* m_image;
        //One image per frame
        std::vector<BasicFrame> m_frames;

        int m_fps;
        float m_time_per_frame;
        float m_current_animation_time;
        float m_current_frame_time;
        int m_current_frame;

        bool m_playing;
        bool m_loop;
        bool m_backwards;

    private:
};

#endif //BASIC_FRAME_ANIMATION_HPP
