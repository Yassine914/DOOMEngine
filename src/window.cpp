#include "../include/window.h"

#include <iostream>

namespace win {

i32 Window::width = DEF_WIDTH, Window::height = DEF_HEIGHT;

void Window::ErrorCallback(i32 error, const char *description)
{
    fprintf(stderr, "error: %s\n", description);
}

void Window::OnWindowResize(GLFWwindow *window, i32 width, i32 height)
{
    Window::SetWindowSize(width, height);
}

void Window::FrameBufferSizeCallback(GLFWwindow *window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
}

void Window::InitializeWindow()
{
    // initialize glfw.

    if(!glfwInit())
    {
        ErrorCallback(1, "failed to init GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_VRS_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_VRS_MINOR);

    glfwSetErrorCallback(Window::ErrorCallback);

    if(Window::resizeable)
    {
        // TODO: fix frame resizing
        // glfwSetWindowSizeCallback(Window::window, Window::OnWindowResize);
        // glfwSetFramebufferSizeCallback(Window::window, Window::FrameBufferSizeCallback);
    }
    // clang-format off

    // TODO: handle fullscreen

    Window::window = glfwCreateWindow(
        Window::GetWidth(), Window::GetHeight(), 
        Window::GetTitle().c_str(), 
        NULL, NULL);

    // clang-format on

    if(!Window::window)
    {
        ErrorCallback(1, "window was not correctly initialized");
        glfwTerminate();
    }

    // TODO: setup OpenGL context.
    glfwMakeContextCurrent(Window::window);
}

void Window::Run()
{
    while(!glfwWindowShouldClose(Window::window))
    {
        std::cout << "game loop" << std::endl;

        // TODO: setup display function.
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }
}

Window::~Window()
{
    glfwDestroyWindow(Window::window);
    glfwTerminate();
}

} // namespace win