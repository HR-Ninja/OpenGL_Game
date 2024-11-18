#pragma once
#include <iostream>
#include "OpenGL.hpp"

namespace Time {
	static float deltaTime = 0;
	float lastFrame = 0;

	inline void CalculateDeltaTime() {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	static float FPS = 0;

	inline void ShowFPS() {
		FPS = 1 / deltaTime;

		std::cout << "FPS: " << FPS << std::endl;
	}

}