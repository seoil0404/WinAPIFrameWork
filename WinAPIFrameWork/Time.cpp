#include "Time.h"
#include <chrono>
#include "Debug.h"

float Time::deltaTime;

static std::chrono::steady_clock::time_point lastFrameTime;

float Time::DeltaTime()
{
    return deltaTime;
}

void Time::Update()
{   
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<float>(now - lastFrameTime).count();
    lastFrameTime = now;;
}

void Time::Awake()
{
    lastFrameTime = std::chrono::high_resolution_clock::now();
}
