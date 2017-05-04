#include "vector2.hpp"
#include <cmath>

//explicit template specialization declaration
template class Vector2<int>;
template class Vector2<float>;
template class Vector2<double>;

template<typename T>
Vector2<T>& Vector2<T>::operator= (const Vector2<T>& other)
{
    if(this != &other)//object is different, we can copy it
    {
        Vector2 tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator= (Vector2<T>&& other) noexcept
{
    if(this != &other)//object is diffrent we can move it
    {
        m_x = std::move(other.m_x);
        m_y = std::move(other.m_y);
    }

    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator+ (const Vector2<T>& other) const
{
    Vector2 auxilia {*this};
    return auxilia += other;
}

template<typename T>
Vector2<T> Vector2<T>::operator- (const Vector2<T>& other) const
{
    Vector2 auxilia {*this};
    return auxilia -= other;
}

template<typename T>
Vector2<T>& Vector2<T>::operator+= (const Vector2<T>& other)
{
    this->m_x += other.m_x;
    this->m_y += other.m_y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-= (const Vector2<T>& other)
{
    this->m_x -= other.m_x;
    this->m_y -= other.m_y;
    return *this;
}

template<typename T>
bool Vector2<T>::operator== (const Vector2<T>& other) const
{
    return this->m_x == other.m_x && this->m_y == other.m_y;
}

template<typename T>
bool Vector2<T>::operator!= (const Vector2<T>& other) const
{
    return !(*this == other);
}

template<typename T>
bool Vector2<T>::operator< (const Vector2<T>& other) const
{
    return this->m_x < other.m_x && this->m_y < other.m_y;
}

template<typename T>
bool Vector2<T>::operator> (const Vector2<T>& other) const
{
    return this->m_x > other.m_x && this->m_y > other.m_y;
}

template<typename T>
bool Vector2<T>::operator<= (const Vector2<T>& other) const
{
    return (*this < other || *this == other);
}

template<typename T>
bool Vector2<T>::operator>= (const Vector2<T>& other) const
{
    return (*this > other || *this == other);
}

template<typename T>
template<typename V>
Vector2<T> Vector2<T>::operator* (const V& scalar) const
{
    Vector2 auxilia {*this};
    auxilia.m_x *= scalar;
    auxilia.m_y *= scalar;
    return auxilia;
}
template<typename T>
template<typename V>
Vector2<T> Vector2<T>::operator/ (const V& scalar) const
{
    Vector2 auxilia {*this};
    auxilia.m_x /= scalar;
    auxilia.m_y /= scalar;
    return auxilia;
}

template<typename T>
template<typename V>
Vector2<T>& Vector2<T>::operator*= (const V& scalar)
{
    this->m_x *= scalar;
    this->m_y *= scalar;
    return *this;
}
template<typename T>
template<typename V>
Vector2<T>& Vector2<T>::operator/= (const V& scalar)
{
    this->m_x /= scalar;
    this->m_y /= scalar;
    return *this;
}

template<typename T>
Vector2<T> Vector2<T>::Normalized()
{
    Vector2 auxilia {*this};
    float length = this->Length();
    auxilia.m_x /= length;
    auxilia.m_y /= length;
    return auxilia;
}

template<typename T>
void Vector2<T>::Normalize()
{
    float length = this->Length();
    m_x /= length;
    m_y /= length;
}

template<typename T>
float Vector2<T>::Length()
{
    return std::sqrt( m_x * m_x + m_y * m_y );
}

template<>
Vector2<int> Vector2<int>::Lerp(const Vector2<int>& other, const float& t, const bool& this_is_start)
{
    if(this_is_start)
        return { static_cast<int>(t * m_x + (1 - t) * other.m_x), static_cast<int>(t * m_y + (1 - t) * other.m_y) };
    else
        return { static_cast<int>((1 - t) * m_x + t * other.m_x), static_cast<int>((1 - t) * m_y + t * other.m_y) };
}

template<typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2<T>& other, const float& t, const bool& this_is_start)
{
    if(this_is_start)
        return { t * m_x + (1 - t) * other.m_x, t * m_y + (1 - t) * other.m_y };
    else
        return { (1 - t) * m_x + t * other.m_x, (1 - t) * m_y + t * other.m_y };
}

template<typename T>
Vector2<T> Lerp(const Vector2<T>& start, const Vector2<T>& end, const float& t)
{
    // return { start.m_x + (end.m_x - start.m_x) * t, start.m_y + (end.m_y - start.m_y) * t };
    return { (1 - t) * start.m_x + t * end.m_x, (1 - t) * start.m_y + t * end.m_y };
}
