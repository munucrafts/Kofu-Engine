#pragma once
#include "iostream"
#include "Engine.h"

int main()
{
	Engine::GetEngine().InitEngine();
	Engine::GetEngine().RunEngine();
	Engine::GetEngine().QuitEngine();

	return 0;
}