#pragma once
#include "Main.h"

class Time
{
public:
	static float DeltaTime();
private:
	static float deltaTime;
	static void Update();
	static void Awake();
	friend void System::Update();
	friend void System::Awake();
};