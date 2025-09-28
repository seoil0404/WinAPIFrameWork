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

public:
	void AddComponent(Component* component);

protected:
	std::vector<Component*> components;

	void AwakeComponents();
	void UpdateComponents();
};