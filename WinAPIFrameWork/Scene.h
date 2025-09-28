#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include "Object.h"

class Scene
{
public:
	Scene(std::vector<Object*> objects);
	Scene();
	~Scene();

public:
	void Awake();
	void Update();
private:
	std::vector<Object*> objects;
};

class SceneManager
{
public:
	static Scene CurrentScene;
};