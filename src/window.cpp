#include "../include/window.h"

// FIXME: remove extra dependencies (add logger class)
#include <iostream>

i32 Window::width = DEF_WIDTH, Window::height = DEF_HEIGHT;

void Window::ErrorCallback(i32 error, const char *description)
{
    std::cout << "\033[30m" << "error: " << description << "\033[00m" << std::endl;
    fprintf(stderr, "error: %s\n", description);
}

void Window::OnWindowResize(GLFWwindow *window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
    Window::SetWindowSize(width, height);
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

    // glfwSetWindowUserPointer(Window::window, reinterpret_cast<void *>(this));
    glfwSetErrorCallback(Window::ErrorCallback);

    if(Window::resizeable)
    {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        // FIXME: frame resizing

        // glfwSetFramebufferSizeCallback(window, nullptr);
    }

    if(Window::fullscreen)
    {
        // TODO: handle fullscreen

        // get the current main monitor
        // get the width and height of the monitor
        // update the Window class
        // set glfw to render fullscreen
    }

    // clang-format off
    Window::window = glfwCreateWindow(
        Window::GetWidth(), Window::GetHeight(), 
        Window::GetTitle().c_str(), 
        nullptr, nullptr);

    // clang-format on

    if(!Window::window)
    {
        ErrorCallback(1, "window was not correctly initialized");
        glfwTerminate();
    }

    // TODO: setup OpenGL context.
    glfwMakeContextCurrent(Window::window);
}

void Window::InitializeResizing()
{
    if(Window::resizeable)
    {
        glfwSetFramebufferSizeCallback(Window::window, Window::OnWindowResize);
    }
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