#include "Main.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "Shape.h"
#include "Object.h"
#include "RenderManager.h"
#include "WinGlobal.h"

void System::Awake()
{
	Shader* shader = ShaderManager::LoadShader("BasicShader.hlsl");
	std::vector<Object*> objects;
	Object* object = new Object();
	object->AddComponent(new TriangleRenderer());
	object->position = Vector3(0.2f, 0.2f, 0);
	objects.push_back(object);

	object = new Object();
	object->AddComponent(new TriangleRenderer());
	object->position = Vector3(-0.2f, -0.2f, 0);
	objects.push_back(object);
	
	SceneManager::CurrentScene = Scene(objects);
	SceneManager::CurrentScene.Awake();

	RenderManager::BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
}

void System::Update()
{
	SceneManager::CurrentScene.Update();
}

void System::Render()
{
	RenderManager::Render();	
}
