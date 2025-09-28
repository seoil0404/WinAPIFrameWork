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
	ShaderManager::SetBasicShader("BasicShader.hlsl");
	std::vector<Object*> objects;
	Object* object = new Object();
	object->AddComponent(new TriangleRenderer());
	object->position = Vector3(0.2f, 0, 0);
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
	g_context->ClearRenderTargetView(g_renderTargetView, RenderManager::BackgroundColor.data());

	RenderManager::Render();

	g_swapChain->Present(1, 0);
}
