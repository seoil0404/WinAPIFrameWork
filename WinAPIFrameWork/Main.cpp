#include "Main.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "Shape.h"
#include "Object.h"
#include "RenderManager.h"
#include "WinGlobal.h"
#include "Time.h"

Object* object = nullptr;
Object* object2 = nullptr;

void System::Awake()
{
	Shader* shader = ShaderManager::LoadShader("BasicShader.hlsl");
	std::vector<Object*> objects;

	object = new Object();
	object->AddComponent(new CubeRenderer());
	object->position = Vector3(0.3f, 0.0f, 0);

	object2 = new Object();
	object2->AddComponent(new CubeRenderer());
	object2->position = Vector3(0.3f, 0.0f, 0);
	
	objects.push_back(object);
	//objects.push_back(object2);
	
	SceneManager::CurrentScene = Scene(objects);
	SceneManager::CurrentScene.Awake();

	RenderManager::BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	Time::Awake();
}

void System::Update()
{
	Time::Update();
	//object->rotation.SetX(object->rotation.GetX() + 0.05f);
	object->rotation.SetY(object->rotation.GetY() - 0.05f);
	//object->rotation.SetZ(object->rotation.GetZ() + 0.05f);

	//object2->rotation.SetX(object2->rotation.GetX() + 0.05f);
	//object2->rotation.SetY(object2->rotation.GetY() - 0.05f);
	//object2->rotation.SetZ(object2->rotation.GetZ() + 0.05f);
	SceneManager::CurrentScene.Update();
}

void System::Render()
{
	RenderManager::Render();	
}
