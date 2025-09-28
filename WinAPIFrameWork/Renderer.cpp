#include "Renderer.h"
#include "Vector.h"
#include "Object.h"
#include "Debug.h"

void Renderer::SyncPosition(Vector3* vertices, unsigned int vertexSize)
{
	Vector3 basePosition = object->position;

	for (int index = 0; index < vertexSize; index++)
	{
		vertices[index].x += basePosition.x;
		vertices[index].y += basePosition.y;
		vertices[index].z += basePosition.z;
	}
}
