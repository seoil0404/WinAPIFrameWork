#pragma once
#include "Vector.h"
#include <vector>
#include <DirectXMath.h>

class Component;

class Object
{
public:
	void Awake();
	void Update();

	~Object();

public:
	Vector3 position;
	Vector3 scale = { 1,1,1 };
	Vector3 rotation = { 0, 0, 0 };

public:
	DirectX::XMMATRIX GetWorldMatrix() const;

public:
	void AddComponent(Component* component);

protected:
	std::vector<Component*> components;

	void AwakeComponents();
	void UpdateComponents();
};