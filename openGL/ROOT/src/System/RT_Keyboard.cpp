#include "RT_Keyboard.h"

RT_Keyboard *RT_Keyboard::INSTANCE = nullptr;

RT_Keyboard::RT_Keyboard()
{}

RT_Keyboard::~RT_Keyboard()
{
	if (INSTANCE)
	{
		delete INSTANCE;
		INSTANCE = nullptr;
	}

	released.clear();
	pressed.clear();
	down.clear();
}

RT_Keyboard *RT_Keyboard::GetInstance()
{
	if (!INSTANCE)
	{
		INSTANCE = new RT_Keyboard();
	}

	return INSTANCE;
}

bool RT_Keyboard::IsPressed(const int key)
{
	return (pressed.find(key) != pressed.end() && 
			pressed[key] != false);
}

bool RT_Keyboard::IsDown(const int key)
{
	return (down.find(key) != down.end() &&
		    down[key] != false);
}

bool RT_Keyboard::IsReleased(const int key)
{
	return (released.find(key) != released.end() &&
			released[key] != false);
}

void RT_Keyboard::Set(const int key, const int action)
{
	if (action == GLFW_PRESS)
	{
		pressed[key] = true;
		down[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		down.erase(key);
		released[key] = true;
	}
}

void RT_Keyboard::Update()
{
	pressed.clear();
	released.clear();
}
