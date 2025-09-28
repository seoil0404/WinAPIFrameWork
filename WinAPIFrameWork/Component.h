#pragma once

class Object;

class Component
{
public:
	void Awake(Object* object);
	virtual void Update() {}
protected:
	virtual void Awake() {}
	Object* object;
};