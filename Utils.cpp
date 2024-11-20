#include "Utils.hpp"

void Time::CalculateDeltaTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Time::ShowFPS() {
	FPS = 1 / deltaTime;
	std::cout << "FPS: " << FPS << std::endl;
}