#pragma once
#include <iostream>
#include "OpenGL.hpp"

namespace Time {
	inline float deltaTime;
	inline float lastFrame;
	inline float FPS = 0;

	void CalculateDeltaTime();
	void ShowFPS();
}