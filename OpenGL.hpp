#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <assert.h>
#include "Settings.hpp"


namespace OpenGL {

	inline GLFWwindow* m_window;

	void Init();

	bool isRunning();

	void Begin();


	void End();


	void Cleanup();

}