#include "Main.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "Shape.h"
#include "Object.h"
#include "RenderManager.h"
#include "WinGlobal.h"
#include "Time.h"

void System::Awake()
{
	Shader* shader = ShaderManager::LoadShader("BasicShader.hlsl");
	std::vector<Object*> objects;
	Object* object = new Object();
	Object* object2 = new Object();
	object2->AddComponent(new BoxRenderer());
	object2->position = Vector3(0.35f, 0.0f, 0);
	object2->scale *= 0.5f;
	objects.push_back(object2);
	object->AddComponent(new TriangleRenderer());
	object->position = Vector3(0.0f, 0.0f, 0);
	objects.push_back(object);
	
	SceneManager::CurrentScene = Scene(objects);
	SceneManager::CurrentScene.Awake();

	RenderManager::BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };

	Time::Awake();
}

void System::Update()
{
	Time::Update();
	SceneManager::CurrentScene.Update();
}

void System::Render()
{
	RenderManager::Render();	
}
