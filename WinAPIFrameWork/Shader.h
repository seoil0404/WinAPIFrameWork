#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <map>
#include <filesystem>

struct Shader
{
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};

class ShaderManager
{
public:
	static Shader* LoadShader(std::filesystem::path filePath);
private:
	static std::map<std::string, Shader*> shaderData;
};