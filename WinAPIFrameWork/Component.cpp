#include "Component.h"
#include "Object.h"
#include "Debug.h"

void Component::Awake(Object* object)
{
	this->object = object;

	Awake();
}