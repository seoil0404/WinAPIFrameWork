#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct Vector3
{
private:
    XMFLOAT3 data;

public:
    float GetX() const;
    float GetY() const;
    float GetZ() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

public:
    Vector3();
    Vector3(float x, float y, float z);

    XMVECTOR ToXM() const;
    void FromXM(FXMVECTOR xm);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float mul) const;
    Vector3 operator/(float mul) const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
    Vector3& operator*=(float mul);
    Vector3& operator/=(float suv);

    bool operator==(const Vector3& other) const;
    bool operator!=(const Vector3& other) const;

    static float Dot(const Vector3& a, const Vector3& b);
    static Vector3 Cross(const Vector3& a, const Vector3& b);
    float Length() const;

    Vector3 Normalize() const;

    static Vector3 Zero();
    static Vector3 One();
};

struct Vector2
{
	float x, y;

	Vector2(float x, float y);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float mul) const;
	bool operator==(const Vector2& other) const;
};