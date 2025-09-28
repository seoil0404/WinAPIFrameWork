#pragma once
#include "Main.h"
#include <vector>
#include <array>

class ID3D11Buffer;
class Shader;
class Vector3;

struct DrawCall
{
	unsigned int indexCount;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Shader* shader;
};

class RenderManager
{
public:
	static std::array<float, 4> BackgroundColor;
public:
	static void Draw(
		unsigned int indexCount,
		ID3D11Buffer* vertexBuffer, 
		ID3D11Buffer* indexBuffer,
		Shader* shader);
public:
	static ID3D11Buffer* GetVertexBuffer(Vector3* vertices, unsigned int size);
	static ID3D11Buffer* GetIndexBuffer(unsigned int* indices, unsigned int size);
private:
	static std::vector<DrawCall> drawCalls;
	static void Render();

	friend void System::Render();
};