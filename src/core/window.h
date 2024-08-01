#pragma once

#include "defines.h"
#include "logger.h"
#include <string>

#include "../../thirdparty/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../input/joystick.h"

#define DEF_HEIGHT 480
#define DEF_WIDTH  640

#define GL_VRS_MAJOR 4
#define GL_VRS_MINOR 3

class Window
{
    private:
    static i32 width, height;
    i32 monitorWidth, monitorHeight;
    bool fullscreen, resizeable, vsync;
    std::string title = "GLFW window";

    static Joystick mainJoystick;

    protected:
    GLFWwindow *window;
    GLFWmonitor *monitor;

    public:
    // clang-format off
    Window()
        :fullscreen{false}, resizeable{true},
         vsync{true}, title{"GLFW window"},
         monitorWidth{DEF_WIDTH}, monitorHeight{DEF_HEIGHT}
    {
        width = DEF_WIDTH;
        height = DEF_HEIGHT;
    }

    // clang-format on

    // getter methods
    inline i32 GetWidth() const { return Window::width; }
    inline i32 GetHeight() const { return Window::height; }

    inline std::string GetTitle() const { return this->title; }

    inline GLFWwindow *GetWindow() const { return this->window; }
    inline GLFWmonitor *GetMonitor() const { return this->monitor; }

    inline bool VSyncEnabled() const { return this->vsync; }

    // setter methods
    static inline void SetWindowSize(i32 width, i32 height)
    {
        if(width <= 0 || height <= 0)
        {
            Window::SetDefaultWindowSize();
            return;
        }

        Window::width = width;
        Window::height = height;
    }

    static inline void SetDefaultWindowSize()
    {
        width = DEF_WIDTH;
        height = DEF_HEIGHT;
    }

    inline void SetFullscreen(bool fs) { this->fullscreen = fs; }
    inline void SetResizeable(bool rs) { this->resizeable = rs; }
    inline void SetVSync(bool vs) { this->vsync = vs; }
    inline void SetWindowTitle(std::string title) { this->title = title; }

    // initialization
    void InitializeWindow();

    // main game loop
    inline bool WindowShouldClose() { return glfwWindowShouldClose(window); }
    inline void SetWindowShouldClose(bool shouldClose) { glfwSetWindowShouldClose(window, shouldClose); }
    inline void NewFrame()
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // glfw callbacks
    static void ErrorCallback(i32 error, const char *description);
    static void OnWindowResize(GLFWwindow *window, i32 width, i32 height);

    // joystick input
    inline bool IsJoystickPresent() { return mainJoystick.IsPresent(); }
    inline void UpdateJoystick() { mainJoystick.Update(); }

    // extras
    inline void EnableCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
    inline void DisableCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }

    // destructor
    ~Window();
};