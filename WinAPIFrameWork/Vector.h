#pragma once

struct Vector3
{
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float mul) const;
	bool operator==(const Vector3& other) const;
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