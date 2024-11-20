#include "OpenGL.hpp"


void OpenGL::Init() {
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

bool OpenGL::isRunning() {
	return !glfwWindowShouldClose(m_window);
}

void OpenGL::Begin() {
	glfwPollEvents();
}


void OpenGL::End() {
	glfwSwapBuffers(m_window);
}


void OpenGL::Cleanup() {
	if (m_window) {
		glfwDestroyWindow(m_window);
	}
	glfwTerminate();
}