#pragma once
#include "Vector.h"
#include <vector>

class Component;

class Object
{
public:
	void Awake();
	void Update();

	~Object();

public:
	Vector3 position;
	float scale = 1;

public:
	void AddComponent(Component* component);

protected:
	std::vector<Component*> components;

	void AwakeComponents();
	void UpdateComponents();
};