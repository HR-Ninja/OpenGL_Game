#include <iostream>

#include "OpenGL.hpp"
#include "Settings.hpp"
#include "ResourceManager.hpp"
#include "Utils.hpp"
#include "Game.hpp"


// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

inline Game game(Settings::g_window.SCREEN_WIDTH, Settings::g_window.SCREEN_HEIGHT);


int main()
{

    OpenGL::Init();

    glfwSetKeyCallback(OpenGL::m_window, key_callback);
    glfwSetFramebufferSizeCallback(OpenGL::m_window, framebuffer_size_callback);


    game.Init();


    while (OpenGL::isRunning())
    {
        Time::CalculateDeltaTime();

        OpenGL::Begin();

        // manage user input
        // -----------------
        game.ProcessInput(Time::deltaTime);


        // update game state
        // -----------------
        game.Update(Time::deltaTime);


        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game.Render();

        Time::ShowFPS();

        OpenGL::End();

    }

    ResourceManager::Clear();
    OpenGL::Cleanup();

	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            game.Keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    
    Settings::g_window.SCREEN_WIDTH = width;
    Settings::g_window.SCREEN_HEIGHT = height;

    glViewport(0, 0, width, height);
}