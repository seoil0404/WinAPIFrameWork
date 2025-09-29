#pragma once
#include "Main.h"
#include <vector>
#include <array>
#include <DirectXMath.h>
#include "Object.h"

struct ID3D11Buffer;
struct Shader;
struct Vector3;

struct DrawCall
{
	DrawCall(
		const Object& object,
		unsigned int indexCount,
		ID3D11Buffer* vertexBuffer,
		ID3D11Buffer* indexBuffer,
		Shader* shader
	);

	const Object& object;
	unsigned int indexCount;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Shader* shader;
};

struct ConstantMVPBuffer
{
	DirectX::XMMATRIX mvp;
};

class RenderManager
{
public:
	static std::array<float, 4> BackgroundColor;
public:
	static void Draw(
		const Object& object,
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
	static DirectX::XMMATRIX GetMVP(const Object& object);

	friend void System::Render();
};