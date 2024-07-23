#include "window.h"

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

    glfwSetErrorCallback(Window::ErrorCallback);

    if(Window::fullscreen)
    {
        // TODO: handle fullscreen

        // get the current main monitor
        // get the width and height of the monitor
        // update the Window class
        // set glfw to render fullscreen
    }

    Window::monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *screen = glfwGetVideoMode(monitor);
    Window::monitorWidth = screen->width;
    Window::monitorHeight = screen->width;

    // clang-format off
    if(Window::fullscreen)
    {
        Window::SetWindowSize(Window::monitorWidth, Window::monitorHeight);

        Window::window = glfwCreateWindow(
            Window::monitorWidth, Window::monitorHeight,
            Window::GetTitle().c_str(),
            Window::monitor, nullptr);
    }
    else
    {
        Window::window = glfwCreateWindow(
            Window::GetWidth(), Window::GetHeight(), 
            Window::GetTitle().c_str(), 
            nullptr, nullptr);
    }
    // clang-format on

    if(!Window::window)
    {
        ErrorCallback(1, "window was not correctly initialized");
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window::window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        // TODO: logging errors.
        ErrorCallback(1, "couldn't load OpenGL");
    }

    if(Window::VSyncEnabled()) glfwSwapInterval(1);

    if(Window::resizeable)
    {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwSetFramebufferSizeCallback(Window::window, Window::OnWindowResize);
    }
}

void Window::Run()
{
    while(!glfwWindowShouldClose(Window::window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: handle input

        // Create a function that handles input
        //      in an input class

        // TODO: handle rendering

        // Create a function that handles rendering
        //       in the renderer class

        // check events and swap buffers
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }
}

Window::~Window()
{
    glfwDestroyWindow(Window::window);
    glfwTerminate();
}