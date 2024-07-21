#include "../include/window.h"

namespace win {

void ErrorCallback(i32 error, const char *description)
{
    fprintf(stderr, "error: %s\n", description);
}

void Window::FrameBufferSizeCallback(GLFWwindow *window, i32 width, i32 height)
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

    glfwSetErrorCallback(ErrorCallback);
    glfwSetFramebufferSizeCallback(Window::window, Window::FrameBufferSizeCallback);

    // clang-format off

    // TODO: handle fullscreen

    Window::window = glfwCreateWindow(
        Window::GetWidth(), Window::GetHeight(), 
        Window::GetTitle().c_str(), NULL, NULL);

    if(!Window::window)
    {
        ErrorCallback(1, "window was not correctly initialized");
        glfwTerminate();
    }

    // TODO: setup OpenGL context.

    glfwMakeContextCurrent(Window::window);
    // clang-format on
}

// TODO: handle resizing
void Window::Run()
{
    while(!glfwWindowShouldClose(Window::window))
    {
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