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

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	ID3D11Buffer* vertexBuffer = RenderManager::GetVertexBuffer(vertices, VERTEX_SIZE);
	ID3D11Buffer* indexBuffer = RenderManager::GetIndexBuffer(indices, INDEX_SIZE);

	RenderManager::Draw((*object), INDEX_SIZE, vertexBuffer, indexBuffer, ShaderManager::LoadShader("BasicShader.hlsl"));

	delete[] vertices;
	delete[] indices;
}

void BoxRenderer::Update()
{
	constexpr unsigned int VERTEX_SIZE = 4;
	constexpr unsigned int INDEX_SIZE = 6;

	auto vertices = new Vector3[VERTEX_SIZE]
	{
		{ 0.5f,  0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f }
	};
	auto indices = new unsigned int[INDEX_SIZE]
	{
		0, 1, 2,
		0, 2, 3
	};

	ID3D11Buffer* vertexBuffer = RenderManager::GetVertexBuffer(vertices, VERTEX_SIZE);
	ID3D11Buffer* indexBuffer = RenderManager::GetIndexBuffer(indices, INDEX_SIZE);

	RenderManager::Draw((*object), INDEX_SIZE, vertexBuffer, indexBuffer, ShaderManager::LoadShader("BasicShader.hlsl"));

	delete[] vertices;
	delete[] indices;
}

void CubeRenderer::Update()
{
	constexpr unsigned int VERTEX_SIZE = 8;
	constexpr unsigned int INDEX_SIZE = 36;

	auto vertices = new Vector3[VERTEX_SIZE]
	{
		{ -0.5f, -0.5f, -0.5f }, // 0: left-bottom-back
		{ -0.5f,  0.5f, -0.5f }, // 1: left-top-back
		{  0.5f,  0.5f, -0.5f }, // 2: right-top-back
		{  0.5f, -0.5f, -0.5f }, // 3: right-bottom-back
		{ -0.5f, -0.5f,  0.5f }, // 4: left-bottom-front
		{ -0.5f,  0.5f,  0.5f }, // 5: left-top-front
		{  0.5f,  0.5f,  0.5f }, // 6: right-top-front
		{  0.5f, -0.5f,  0.5f }  // 7: right-bottom-front
	};

	auto indices = new unsigned int[INDEX_SIZE]
	{
			// 뒷면 (z = -0.5)
			0, 1, 2,
			0, 2, 3,

				// 앞면 (z = +0.5)
				4, 6, 5,
				4, 7, 6,

				// 왼쪽면 (x = -0.5)
				4, 5, 1,
				4, 1, 0,

				// 오른쪽면 (x = +0.5)
				3, 2, 6,
				3, 6, 7,

				// 윗면 (y = +0.5)
				1, 5, 6,
				1, 6, 2,

				// 아랫면 (y = -0.5)
				4, 0, 3,
				4, 3, 7
	};

	ID3D11Buffer* vertexBuffer = RenderManager::GetVertexBuffer(vertices, VERTEX_SIZE);
	ID3D11Buffer* indexBuffer = RenderManager::GetIndexBuffer(indices, INDEX_SIZE);

	RenderManager::Draw((*object), INDEX_SIZE, vertexBuffer, indexBuffer, ShaderManager::LoadShader("BasicShader.hlsl"));

	delete[] vertices;
	delete[] indices;
}