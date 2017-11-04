#include "quaternion.hpp"
#include <utility>

//<f> Constructors & operator=
Quaternion::Quaternion()
{
    
}

Quaternion::~Quaternion() noexcept
{

}

Quaternion::Quaternion(const Quaternion& other)
{

}

Quaternion::Quaternion(Quaternion&& other) noexcept
{

}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
    if(this != &other)//not same ref
    {
        auto tmp(other);
        *this = std::move(tmp);
    }

    return *this;
}

Quaternion& Quaternion::operator=(Quaternion&& other) noexcept
{
    if(this != &other)//not same ref
    {
        //move here
    }
    return *this;
}
//</f> /Constructors & operator=
