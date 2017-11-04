#ifndef BACKGROUND_STARS_HPP
#define BACKGROUND_STARS_HPP

#include "behaviour_script.hpp"
#include "image.hpp"

class BackgroundStars : public BehaviourScript
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        BackgroundStars();
        /** brief Default destructor */
        virtual ~BackgroundStars() noexcept;

        /** brief Copy constructor */
        BackgroundStars(const BackgroundStars& other);
        /** brief Move constructor */
        BackgroundStars(BackgroundStars&& other) noexcept;

        /** brief Copy operator */
        BackgroundStars& operator= (const BackgroundStars& other);
        /** brief Move operator */
        BackgroundStars& operator= (BackgroundStars&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Virtual Methods
        Script* Clone() override;

        void Update(float delta_time) override;
        //</f> /Virtual Methods

        //<f> Getters/Setters
        float UpdateInterval() const;
        void UpdateInterval(float interval);

        float RotationAngle() const;
        void RotationAngle(float angle);
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        Image* m_image;
        float m_current_time;
        float m_update_interval;
        float m_angle;
    private:
};

#endif //BACKGROUND_STARS_HPP
