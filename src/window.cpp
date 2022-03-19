#include "window.hpp"

#include <iostream>

void error_callback(int error, const char* description)
{
    std::cerr << "[ERROR] " << description << std::endl;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Window::Window(const Properties& props)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    m_Properties = props;
}

void Window::Init(bool vsync)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_Window = glfwCreateWindow(m_Properties.Width, m_Properties.Height, m_Properties.Title.c_str(),
                                NULL, NULL);
    if (!m_Window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(m_Window, key_callback);

    glfwMakeContextCurrent(m_Window);
    glewInit();
    glfwSwapInterval(vsync);
}

void Window::Update()
{
    glfwGetFramebufferSize(m_Window, reinterpret_cast<int*>(&m_Properties.Width),
                           reinterpret_cast<int*>(&m_Properties.Height));
    glViewport(0, 0, m_Properties.Width, m_Properties.Height);

    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void Window::Terminate()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}