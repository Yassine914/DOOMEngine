#pragma once

#include "../core/defines.h"

#include "../../thirdparty/include/glad/glad.h"
#include "../../thirdparty/include/glfw/glfw3.h"

class Mouse
{
    private:
    static f64 x, y;
    static f64 lastX, lastY;
    static f64 dx, dy;
    static f64 scrollDX, scrollDY;

    static bool firstMouse;

    static bool buttons[];
    static bool buttonsChanged[];

    public:
    Mouse() {}

    // mouse callbacks
    static void CursorPosCallback(GLFWwindow *window, f64 x, f64 y);
    static void MouseButtonCallback(GLFWwindow *window, i32 button, i32 action, i32 mods);
    static void MouseWheelCallback(GLFWwindow *window, f64 dx, f64 dy);

    // getters -> mouse movement
    static f64 GetMouseX();
    static f64 GetMouseY();

    static f64 GetDX();
    static f64 GetDY();

    static f64 GetScrollDX();
    static f64 GetScrollDY();

    // getters -> buttons
    static bool GetButton(i32 button);
    static bool ButtonChanged(i32 button);
    static bool GetButtonUp(i32 button);
    static bool GetBottonDown(i32 button);

    ~Mouse() = default;
};