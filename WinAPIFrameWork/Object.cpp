#include "Object.h"
#include "Component.h"

void Object::Awake()
{
	AwakeComponents();
}

void Object::Update()
{
	UpdateComponents();
}

Object::~Object()
{

}

DirectX::XMMATRIX Object::GetWorldMatrix() const
{
	using namespace DirectX;
	
	XMMATRIX S = XMMatrixScaling(scale.GetX(), scale.GetY(), scale.GetZ());
	XMMATRIX R = XMMatrixRotationRollPitchYaw(rotation.GetX(), rotation.GetY(), rotation.GetZ());
	XMMATRIX T = XMMatrixTranslation(position.GetX(), position.GetY(), position.GetZ());

	return S * R * T;
}

void Object::AddComponent(Component* component)
{
	components.push_back(component);
}

void Object::AwakeComponents()
{
	for (int index = 0; index < components.size(); index++)
		components[index]->Awake(this);
}

void Object::UpdateComponents()
{
	for (int index = 0; index < components.size(); index++)
		components[index]->Update();
}
