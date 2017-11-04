#ifndef QUATERNION_HPP
#define QUATERNION_HPP

class Quaternion
{
    public:
        //<f> Constructors & operator=
        /** brief Default constructor */
        Quaternion();
        /** brief Default destructor */
        virtual ~Quaternion() noexcept;

        /** brief Copy constructor */
        Quaternion(const Quaternion& other);
        /** brief Move constructor */
        Quaternion(Quaternion&& other) noexcept;

        /** brief Copy operator */
        Quaternion& operator= (const Quaternion& other);
        /** brief Move operator */
        Quaternion& operator= (Quaternion&& other) noexcept;
        //</f> /Constructors & operator=

        //<f> Operations
        
        //</f> /Operations

        //<f> Virtual Methods

        //</f> /Virtual Methods

        //<f> Getters/Setters
        Quaternion EulerAngles() const;
        Quaternion RadianAngles();
        //</f> /Getters/Setters

    protected:
        // vars and stuff
        float m_x;
        float m_y;
        float m_z;
        float m_w;
    private:
};

#endif //QUATERNION_HPP
