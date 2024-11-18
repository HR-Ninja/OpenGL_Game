#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <assert.h>
#include "Settings.hpp"


namespace OpenGL {

	static GLFWwindow* m_window;

	inline void Init() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, false);

		m_window = glfwCreateWindow(Settings::g_window.SCREEN_WIDTH, Settings::g_window.SCREEN_HEIGHT, "My Game", nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		// glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "failed to load glad\n";
			exit(1);
		}

		// OpenGL configuration
		// --------------------
		glViewport(0, 0, Settings::g_window.SCREEN_WIDTH, Settings::g_window.SCREEN_HEIGHT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	inline bool isRunning() {
		return !glfwWindowShouldClose(m_window);
	}

	inline void Begin() {
		glfwPollEvents();
	}


	inline void End() {
		glfwSwapBuffers(m_window);
	}


	inline void Cleanup() {
		if (m_window) {
			glfwDestroyWindow(m_window);
		}
		glfwTerminate();
	}

}