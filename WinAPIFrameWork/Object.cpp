#include "Object.h"
#include "Component.h"

void Object::Awake()
{
	AwakeComponents();
}

void Object::Update()
{
	UpdateComponents();
}

Object::~Object()
{

}

void Object::AddComponent(Component* component)
{
	components.push_back(component);
}

void Object::AwakeComponents()
{
	for (int index = 0; index < components.size(); index++)
		components[index]->Awake(this);
}

void Object::UpdateComponents()
{
	for (int index = 0; index < components.size(); index++)
		components[index]->Update();
}
