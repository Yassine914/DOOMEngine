#include "defines.h"
#include <string>

#define DEF_HEIGHT 480
#define DEF_WIDTH 720

namespace win {

class Window
{
    private:
    u32 height, width;
    b8 fullscreen;
    std::string name = "GLFW window";

    public:
    Window() : height{DEF_HEIGHT}, width{DEF_WIDTH}, fullscreen{false}
    {
        // TODO: initialize glfw.
    }

    inline u32 GetHeight() { return this->height; }

    inline u32 GetWidth() { return this->width; }

    inline void SetWindowSize(u32 width, u32 height)
    {
        if(width == 0 || height == 0)
        {
            Window::SetDefaultWindowSize();
            return;
        }

        // TODO: resize window (glfw)
        this->width = width;
        this->height = height;
    }

    inline void SetDefaultWindowSize()
    {
        this->height = DEF_HEIGHT;
        this->width = DEF_WIDTH;
    }

    ~Window() = default;
};

} // namespace win