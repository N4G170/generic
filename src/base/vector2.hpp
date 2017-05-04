#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <type_traits>
#include <iostream>

template<typename T = float>
class Vector2
{
    private:
        T m_x;
        T m_y;

    public:
        static_assert(std::is_same<T,int>::value || std::is_same<T,float>::value || std::is_same<T,double>::value, "Vector2 template can only be <int>, <float> or <double>");
        Vector2(): m_x{0}, m_y{0} {}
        Vector2(const T& x , const T& y): m_x{x}, m_y{y} {}

        Vector2(const Vector2& other): m_x{other.m_x}, m_y{other.m_y} {}
        Vector2( Vector2&& other) noexcept{ m_x = std::move(other.m_x); m_y = std::move(other.m_y); }

        virtual ~Vector2() noexcept {}

        T X() const { return m_x; }
        void X(const T& x) { m_x = x; }
        void X(T&& x) { m_x = std::move(x); }
        T Y() const { return m_y; }
        void Y(const T& y) { m_y = y; }
        void Y(T&& y) { m_y = std::move(y); }

        void Set(const T& x, const T& y){ m_x = x; m_y = y; }
        void Set(T&& x, T&& y){ m_x = std::move(x); m_y = std::move(y); }

        Vector2& operator= (const Vector2& other);
        Vector2& operator= (Vector2&& other) noexcept;

        Vector2 operator+ (const Vector2& other) const;
        Vector2 operator- (const Vector2& other) const;

        Vector2& operator+= (const Vector2& other);
        Vector2& operator-= (const Vector2& other);

        bool operator== (const Vector2& other) const;
        bool operator!= (const Vector2& other) const;
        bool operator< (const Vector2& other) const;
        bool operator> (const Vector2& other) const;
        bool operator<= (const Vector2& other) const;
        bool operator>= (const Vector2& other) const;

        template<typename V>
        Vector2 operator* (const V& scalar) const;
        template<typename V>
        Vector2 operator/ (const V& scalar) const;

        template<typename V>
        Vector2& operator*= (const V& scalar);
        template<typename V>
        Vector2& operator/= (const V& scalar);

        /**
         * Normalizes the vector but does not save the result.
         * \return The not saved normalized vector
         */
        Vector2 Normalized();
        void Normalize();

        float Length();

        void Print() const { std::cout<<"("<< m_x<<", "<<m_y<<")\n"; };
        std::string ToString() const { return ("("+std::to_string(m_x)+", "+std::to_string(m_y)+")\n"); };

        Vector2 Lerp(const Vector2<T>& other, const float& t, const bool& this_is_start = true);
};

template<typename T>
Vector2<T> Lerp(const Vector2<T>& start, const Vector2<T>& end, const float& t = 0.5f);

#endif //VECTOR2_HPP
