#include "defines.h"
#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#define DEF_HEIGHT 480
#define DEF_WIDTH 640

#define GL_VRS_MAJOR 4
#define GL_VRS_MINOR 3

namespace win {

class Window
{
    private:
    static i32 width, height;
    bool fullscreen, resizeable;
    std::string title = "GLFW window";

    protected:
    GLFWwindow *window;

    public:
    // clang-format off
    Window()
        :fullscreen{false}, resizeable{true}, title{"GLFW window"} 
    {
        width = DEF_WIDTH;
        height = DEF_HEIGHT;
    }

    // clang-format on

    // getter methods
    inline i32 GetWidth() { return Window::width; }
    inline i32 GetHeight() { return Window::height; }
    inline std::string GetTitle() { return this->title; }

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

    static void ErrorCallback(i32 error, const char *description);
    static void FrameBufferSizeCallback(GLFWwindow *window, i32 width, i32 height);

    inline void SetFullscreen(bool fs) { this->fullscreen = fs; }
    inline void SetResizeable(bool rs) { this->resizeable = rs; }
    inline void SetWindowTitle(std::string title) { this->title = title; }

    // initialization
    void InitializeWindow();

    // main game loop
    void Run();

    // TODO: setup event to send when window is resized
    static void OnWindowResize(GLFWwindow *window, i32 width, i32 height);

    // destructor
    ~Window();
};

} // namespace win