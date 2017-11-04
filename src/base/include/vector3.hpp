#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <type_traits>
#include <cmath>
#include <utility>
#include <string>

template<typename T = float>
class Vector3
{
    private:
        T m_x;
        T m_y;
        T m_z;

    public:
        //check if we initialize the vector with the right values
        static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Vector3 template can only integrals of floating point types");
        //<f> Constructos & operator=
        Vector3(): m_x{0}, m_y{0}, m_z{0} {}
        Vector3(const T& x , const T& y, const T& z): m_x{x}, m_y{y}, m_z{z} {}
        virtual ~Vector3() noexcept {}

        Vector3(const Vector3& other): m_x{other.X()}, m_y{other.Y()}, m_z{other.Z()} {}
        Vector3( Vector3&& other) noexcept: m_x{std::move(other.X())}, m_y{std::move(other.Y())}, m_z{std::move(other.Z())} {}

        Vector3& operator= (const Vector3& other)
        {
            if(this != &other)
            {
                auto tmp{other};
                *this = std::move(tmp);
            }
            return *this;
        }

        Vector3& operator= (Vector3&& other) noexcept
        {
            if(this != &other)
            {
                m_x = std::move(other.X());
                m_y = std::move(other.Y());
                m_z = std::move(other.Z());
            }
            return *this;
        }
        //</f> /Constructos & operator=

        //<f> Get/Set
        T X() const { return m_x; }
        void X(const T& x) { m_x = x; }
        void X(T&& x) { m_x = std::move(x); }

        T Y() const { return m_y; }
        void Y(const T& y) { m_y = y; }
        void Y(T&& y) { m_y = std::move(y); }

        T Z() const { return m_z; }
        void Z(const T& z) { m_z = z; }
        void Z(T&& z) { m_z = std::move(z); }

        void Set(const T& x, const T& y, const T& z){ m_x = x; m_y = y; m_z = z; }
        void Set(T&& x, T&& y, T&& z){ m_x = std::move(x); m_y = std::move(y); m_z = std::move(z); }
        //</f> /Get/Set

        //<f> Operators
        //the second function (of each) is to allow the use of init lists ex: vector += {1,2,3};
        //<f> Vector Sum/Subtraction/Multiplication/Division
        template<typename U>
        Vector3 operator+ (const Vector3<U>& other) const { return { m_x + other.X(), m_y + other.Y(), m_z + other.Z() }; }
        Vector3 operator+ (const Vector3& other) const { return { m_x + other.X(), m_y + other.Y(), m_z + other.Z() }; }
        template<typename U>
        Vector3 operator- (const Vector3<U>& other) const { return { m_x - other.X(), m_y - other.Y(), m_z - other.Z() }; }
        Vector3 operator- (const Vector3& other) const { return { m_x - other.X(), m_y - other.Y(), m_z - other.Z() }; }
        template<typename U>
        Vector3& operator+= (const Vector3<U>& other) { return *this = *this + other; }
        Vector3& operator+= (const Vector3& other) { return *this = *this + other; }
        template<typename U>
        Vector3& operator-= (const Vector3<U>& other) { return *this = *this - other; }

        template<typename U>
        Vector3 operator* (const Vector3<U>& other) const { return { m_x * other.X(), m_y * other.Y(), m_z * other.Z() }; }
        Vector3 operator* (const Vector3& other) const { return { m_x * other.X(), m_y * other.Y(), m_z * other.Z() }; }
        /** \brief No denominator == 0 check is performed */
        template<typename U>
        Vector3 operator/ (const Vector3<U>& other) const { return { m_x / other.X(), m_y / other.Y(), m_z / other.Z() }; }
        Vector3 operator/ (const Vector3& other) const { return { m_x / other.X(), m_y / other.Y(), m_z / other.Z() }; }
        template<typename U>
        Vector3& operator*= (const Vector3<U>& other) { return *this = *this * other; }
        Vector3& operator*= (const Vector3& other) { return *this = *this * other; }
        /** \brief No denominator == 0 check is performed */
        template<typename U>
        Vector3& operator/= (const Vector3<U>& other) { return *this = *this / other; }
        Vector3& operator/= (const Vector3& other) { return *this = *this / other; }
        //</f> /Vector Sum/Subtraction/Multiplication/Division

        //<f> Logic Operators
        template<typename U>
        bool operator== (const Vector3<U>& other) const { return (m_x == other.X() && m_y == other.Y() && m_z == other.Z()); }
        bool operator== (const Vector3& other) const { return (m_x == other.X() && m_y == other.Y() && m_z == other.Z()); }
        template<typename U>
        bool operator!= (const Vector3<U>& other) const { return (m_x != other.X() || m_y != other.Y() || m_z != other.Z()); }
        bool operator!= (const Vector3& other) const { return (m_x != other.X() || m_y != other.Y() || m_z != other.Z()); }

        template<typename U>
        bool operator< (const Vector3<U>& other) const { return (m_x < other.X() && m_y < other.Y() && m_z < other.Z()); }
        bool operator< (const Vector3& other) const { return (m_x < other.X() && m_y < other.Y() && m_z < other.Z()); }
        template<typename U>
        bool operator> (const Vector3<U>& other) const { return (m_x > other.X() && m_y > other.Y() && m_z > other.Z()); }
        bool operator> (const Vector3& other) const { return (m_x > other.X() && m_y > other.Y() && m_z > other.Z()); }

        template<typename U>
        bool operator<= (const Vector3<U>& other) const { return (*this < other || *this == other); }
        bool operator<= (const Vector3& other) const { return (*this < other || *this == other); }
        template<typename U>
        bool operator>= (const Vector3<U>& other) const { return (*this > other || *this == other); }
        bool operator>= (const Vector3& other) const { return (*this > other || *this == other); }
        //</f> /Logic Operators

        //<f> Scalar Operations
        template<typename V>
        Vector3 operator* (const V& scalar) const { return {m_x * scalar, m_y * scalar, m_z * scalar}; }
        /** \brief No denominator == 0 check is performed */
        template<typename V>
        Vector3 operator/ (const V& scalar) const { return {m_x / scalar, m_y / scalar, m_z / scalar}; }

        template<typename V>
        Vector3& operator*= (const V& scalar) { return *this = *this * scalar; }
        /** \brief No denominator == 0 check is performed */
        template<typename V>
        Vector3& operator/= (const V& scalar) { return *this = *this / scalar; }
        //</f> /Scalar Operations
        //</f> /Operators

        //<f> Other
        /**
         * \brief Normalizes the vector but does not save the result.
         * \return The not saved normalized vector
         */
        Vector3 Normalized()
        {
            auto length = this->Length();
            if(length == 0)
                return {0,0,0};
            return { m_x / length, m_y / length, m_z / length };
        }
        /**
         * \brief Normalizes the vector and stores the result in itself
         */
        void Normalize() { *this  = Normalized(); }

        float Length() { return std::sqrt( m_x * m_x + m_y * m_y + m_z * m_z); }

        float LengthSquared() { return m_x * m_x + m_y * m_y + m_z * m_z; }

        template<typename U>//the target might be of a different numerical type
        float Distance(const Vector3<U>& target) { return (target - *this).Length(); }
        float Distance(const Vector3& target) { return (target - *this).Length(); }

        template<typename U>//the target might be of a different numerical type
        float DistanceSquared(const Vector3<U>& target) { return (target - *this).LengthSquared(); }
        float DistanceSquared(const Vector3& target) { return (target - *this).LengthSquared(); }

        std::string ToString() const { return ("("+std::to_string(m_x)+", "+std::to_string(m_y)+", "+std::to_string(m_z)+")"); };

        /**
         * \brief lerp between two Vector3. Note: this vector will be the min of the range, if you want other to be the min, change the call order
         * @param other         the other vector
         * @param t             the ratio
         * \return  The value between min and max corresponding to the ratio t
         */
        template<typename U>
        Vector3 Lerp(const Vector3<U>& other, const float& t = 0.5f)
        {
            return { t * m_x + (1 - t) * other.X(), t * m_y + (1 - t) * other.Y(), t * m_z + (1 - t) * other.Z() };
        }
        Vector3 Lerp(const Vector3& other, const float& t = 0.5f)
        {
            return { t * m_x + (1 - t) * other.X(), t * m_y + (1 - t) * other.Y(), t * m_z + (1 - t) * other.Z() };
        }

        template<typename U>
        float Dot(const Vector3<U>& other) { return m_x * other.X() + m_y * other.Y() + m_z * other.Z(); }
        float Dot(const Vector3& other) { return m_x * other.X() + m_y * other.Y() + m_z * other.Z(); }
        //</f> /Other
};

/**
 * \brief Lerp using two vectors, return type will use start vector type
 */
template<typename T, typename U>
Vector3<T> Lerp(const Vector3<T>& start, const Vector3<U>& end, const float& t = 0.5f)
{
    return { (1 - t) * start.m_x + t * end.m_x, (1 - t) * start.m_y + t * end.m_y };
}
/**
 * \brief Lerp using two vectors, return type will use end vector type
 */
template<typename T, typename U>
Vector3<T> Lerp(const Vector3<U>& start, const Vector3<T>& end, const float& t = 0.5f)
{
    return { (1 - t) * start.m_x + t * end.m_x, (1 - t) * start.m_y + t * end.m_y };
}

#endif //VECTOR2_HPP
