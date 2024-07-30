#include "mouse.h"

// static variables
f64 Mouse::x = 0, Mouse::y = 0;
f64 Mouse::lastX = 0, Mouse::lastY = 0;
f64 Mouse::dx = 0, Mouse::dy = 0;
f64 Mouse::scrollDX = 0, Mouse::scrollDY = 0;

bool Mouse::firstMouse = true;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = {false};
bool Mouse::buttonsChanged[GLFW_MOUSE_BUTTON_LAST] = {false};

// static methods

// mouse callbacks
void Mouse::CursorPosCallback(GLFWwindow *window, f64 x, f64 y)
{
    Mouse::x = x;
    Mouse::y = y;

    if(firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    dx = x - lastX;
    dy = lastY - y; // inverted

    lastX = x;
    lastY = y;
}
void Mouse::MouseButtonCallback(GLFWwindow *window, i32 button, i32 action, i32 mods)
{
    if(action != GLFW_RELEASE)
    {
        if(!buttons[button])
            buttons[button] = true;
    }
    else
    {
        buttons[button] = false;
    }

    buttonsChanged[button] = (action != GLFW_REPEAT);
}
void Mouse::MouseWheelCallback(GLFWwindow *window, f64 dx, f64 dy)
{
    scrollDX = dx;
    scrollDY = dy;
}

// getters -> mouse movement

f64 Mouse::GetMouseX()
{
    return x;
}
f64 Mouse::GetMouseY()
{
    return y;
}

f64 Mouse::GetDX()
{
    f64 ret = dx;
    dx = 0;

    return ret;
}
f64 Mouse::GetDY()
{
    f64 ret = dy;
    dy = 0;

    return ret;
}

f64 Mouse::GetScrollDX()
{
    f64 ret = scrollDX;
    scrollDX = 0;

    return ret;
}
f64 Mouse::GetScrollDY()
{
    f64 ret = scrollDY;
    scrollDY = 0;

    return ret;
}

// getters -> buttons

bool Mouse::GetButton(i32 button)
{
    return buttons[button];
}

bool Mouse::ButtonChanged(i32 button)
{
    bool ret = buttonsChanged[button];
    buttonsChanged[button] = false;

    return ret;
}

bool Mouse::GetButtonUp(i32 button)
{
    return !buttons[button] && ButtonChanged(button);
}
bool Mouse::GetBottonDown(i32 button)
{
    return buttons[button] && ButtonChanged(button);
}