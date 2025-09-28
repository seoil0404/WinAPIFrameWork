#include "Scene.h"
#include "WinGlobal.h"
#include "Vector.h"
#include "Debug.h"

Scene::Scene(std::vector<Object*> objects) : Scene()
{
    this->objects = objects;

}

Scene::Scene()
{
    
}

Scene::~Scene()
{

}

void Scene::Awake()
{
    for (int index = 0; index < objects.size(); index++)
        objects[index]->Awake();
}

void Scene::Update()
{
    for (int index = 0; index < objects.size(); index++)
        objects[index]->Update();
}