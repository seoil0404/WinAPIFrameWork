#pragma once
#include "Component.h"

struct Vector3;

class Renderer : public Component 
{
protected:
	void SyncVertex(Vector3* vertices, unsigned int vertexSize);
};