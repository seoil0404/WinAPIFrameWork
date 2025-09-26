#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include "File.h"

struct Shader
{
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};

inline Shader g_BasicShader;

class ShaderManager
{
public:
	static void SetBasicShader(std::filesystem::path filePath);
};