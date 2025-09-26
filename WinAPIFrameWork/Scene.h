#pragma once
#include <d3d11.h>
#include <dxgi.h>

class Scene
{
public:
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
protected:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};

class TriangleScene : public Scene
{
public:
	TriangleScene();
};