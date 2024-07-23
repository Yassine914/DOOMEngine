#pragma once

#include "../defines.h"
#include <string>

#include "../../thirdparty/include/glad/glad.h"
#include "../../thirdparty/include/glfw/glfw3.h"

#define DEF_HEIGHT 480
#define DEF_WIDTH 640

#define GL_VRS_MAJOR 4
#define GL_VRS_MINOR 3

class Window
{
    private:
    static i32 width, height;
    i32 monitorWidth, monitorHeight;
    bool fullscreen, resizeable, vsync;
    std::string title = "GLFW window";

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
    inline i32 GetWidth() { return Window::width; }
    inline i32 GetHeight() { return Window::height; }

    inline std::string GetTitle() { return this->title; }

    inline GLFWwindow *GetWindow() { return this->window; }
    inline GLFWmonitor *GetMonitor() { return this->monitor; }

    inline bool VSyncEnabled() { return this->vsync; }

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
    void Run();

    // glfw callbacks
    static void ErrorCallback(i32 error, const char *description);
    static void OnWindowResize(GLFWwindow *window, i32 width, i32 height);

    // destructor
    ~Window();
};