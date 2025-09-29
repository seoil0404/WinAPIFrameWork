#pragma once
#include "Renderer.h"

class TriangleRenderer : public Renderer
{
public:
	void Awake() override;
	void Update() override;
private:
	static constexpr int VERTEX_SIZE = 3;
	static constexpr int INDEX_SIZE = 3;
};

class BoxRenderer : public Renderer
{
public:
	void Update() override;
};

class CubeRenderer : public Renderer
{
public:
	void Update() override;
};