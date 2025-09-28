#include "Shape.h"
#include "Vector.h"
#include "RenderManager.h"
#include "Shader.h"
#include <d3d11.h>

void TriangleRenderer::Awake()
{

}

void TriangleRenderer::Update()
{
	auto vertices = new Vector3[VERTEX_SIZE];
	auto indices = new unsigned int[INDEX_SIZE];

	vertices[0] = { 0.0f,  0.5f, 0.0f };  // 위쪽
	vertices[1] = { 0.5f, -0.5f, 0.0f };  // 오른쪽 아래
	vertices[2] = { -0.5f, -0.5f, 0.0f };  // 왼쪽 아래

	SyncPosition(vertices, VERTEX_SIZE);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	ID3D11Buffer* vertexBuffer = RenderManager::GetVertexBuffer(vertices, VERTEX_SIZE);
	ID3D11Buffer* indexBuffer = RenderManager::GetIndexBuffer(indices, INDEX_SIZE);

	RenderManager::Draw(INDEX_SIZE, vertexBuffer, indexBuffer, &g_BasicShader);
}