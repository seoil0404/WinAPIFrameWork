#include "Renderer.h"
#include "Vector.h"
#include "Object.h"
#include "Debug.h"

void Renderer::SyncVertex(Vector3* vertices, unsigned int vertexSize)
{
	Vector3 basePosition = object->position;

	for (unsigned int index = 0; index < vertexSize; index++)
	{
		vertices[index].x = vertices[index].x * object->scale + basePosition.x;
		vertices[index].y = vertices[index].y * object->scale + basePosition.y;
		vertices[index].z = vertices[index].z * object->scale + basePosition.z;
	}
}
