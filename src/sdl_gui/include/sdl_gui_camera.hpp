namespace sdl_gui
{

#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera
{
    public:
        //<f> Constructors & operator=
        /* Default constructor */
        Camera();
        /* Default destructor */
        virtual ~Camera() noexcept;

        /* Copy constructor */
        Camera(const Camera& other);
        /* Move constructor */
        Camera(Camera&& other) noexcept;

        /* Copy operator */
        Camera& operator= (const Camera& other);
        /* Move operator */
        Camera& operator= (Camera&& other) noexcept;
        //</f>

        //<f> Virtual Methods

        //</f>

        //<f> Getters/Setters

        //</f>

    private:
        // vars and stuff
};

#endif //CAMERA_HPP
}
