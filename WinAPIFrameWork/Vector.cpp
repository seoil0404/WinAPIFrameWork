#include "Vector.h"

Vector3::Vector3() : x(0), y(0), z(0) { }

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) { }

Vector3 Vector3::operator+(const Vector3& other) const
{
    return { x + other.x, y + other.y, z + other.z };
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return { x - other.x, y - other.y, z - other.z };
}

Vector3 Vector3::operator*(float mul) const
{
    return { x * mul, y * mul, z * mul };
}

bool Vector3::operator==(const Vector3& other) const
{
    if (x == other.x && y == other.y && z == other.z)
        return true;
    
    return false;
}


Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& other) const
{
    return { x + other.x, y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const
{
    return { x - other.x, y - other.y };
}

Vector2 Vector2::operator*(float mul) const
{
    return { x * mul, y * mul };
}

bool Vector2::operator==(const Vector2& other) const
{
    if (x == other.x && y == other.y)
        return true;
    
    return false;
}