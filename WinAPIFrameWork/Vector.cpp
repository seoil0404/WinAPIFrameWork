#include "Vector.h"

Vector3::Vector3()
{
    data = XMFLOAT3(0, 0, 0);
}

Vector3::Vector3(float x, float y, float z)
{
    data = XMFLOAT3(x, y, z);
}

float Vector3::GetX() const
{
    return data.x;
}

float Vector3::GetY() const
{
    return data.y;
}

float Vector3::GetZ() const
{
    return data.z;
}

void Vector3::SetX(float x)
{
    data.x = x;
}

void Vector3::SetY(float y)
{
    data.y = y;
}

void Vector3::SetZ(float z)
{
    data.z = z;
}

XMVECTOR Vector3::ToXM() const
{
    return XMLoadFloat3(&data);
}

void Vector3::FromXM(FXMVECTOR vector)
{
    XMStoreFloat3(&data, vector);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    Vector3 vec;
    vec.FromXM(XMVectorAdd(ToXM(), other.ToXM()));
    return vec;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    Vector3 vec;
    vec.FromXM(XMVectorSubtract(ToXM(), other.ToXM()));
    return vec;
}

Vector3 Vector3::operator*(float mul) const
{
    Vector3 vec;
    vec.FromXM(XMVectorScale(ToXM(), mul));
    return vec;
}

Vector3 Vector3::operator/(float mul) const
{
    Vector3 vec;
    vec.FromXM(XMVectorScale(ToXM(), 1.0f / mul));
    return vec;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    FromXM(XMVectorAdd(ToXM(), other.ToXM()));
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    FromXM(XMVectorSubtract(ToXM(), other.ToXM()));
    return *this;
}

Vector3& Vector3::operator*=(float mul)
{
    FromXM(XMVectorScale(ToXM(), mul));
    return *this;
}

Vector3& Vector3::operator/=(float suv)
{
    FromXM(XMVectorScale(ToXM(), 1.0f / suv));
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
    return XMVector3Equal(ToXM(), other.ToXM());
}

bool Vector3::operator!=(const Vector3& other) const
{
    return !(*this == other);
}

float Vector3::Dot(const Vector3& a, const Vector3& b)
{
    return XMVectorGetX(XMVector3Dot(a.ToXM(), b.ToXM()));
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
{
    Vector3 vec;
    vec.FromXM(XMVector3Cross(a.ToXM(), b.ToXM()));
    return vec;
}

float Vector3::Length() const
{
    return XMVectorGetX(XMVector3Length(ToXM()));
}

Vector3 Vector3::Normalize() const
{
    Vector3 vec;
    vec.FromXM(XMVector3Normalize(ToXM()));
    return vec;
}

Vector3 Vector3::Zero() { return Vector3(0, 0, 0); }
Vector3 Vector3::One() { return Vector3(1, 1, 1); }

//=============================================================================================

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