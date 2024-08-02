#include "keyboard.h"

bool Keyboard::keys[GLFW_KEY_LAST] = {false};
bool Keyboard::keysChanged[GLFW_KEY_LAST] = {false};

void Keyboard::KeyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods)
{
    if(action != GLFW_RELEASE)
    {
        if(!keys[key])
            keys[key] = true;
    }
    else
    {
        keys[key] = false;
    }

    keysChanged[key] = (action != GLFW_REPEAT);
}

bool Keyboard::GetKey(i32 key)
{
    return keys[key];
}

bool Keyboard::KeyChanged(i32 key)
{
    bool ret = keysChanged[key];
    keysChanged[key] = false;

    return ret;
}

bool Keyboard::GetKeyUp(i32 key)
{
    return !keys[key] && KeyChanged(key);
}

bool Keyboard::GetKeyDown(i32 key)
{
    return keys[key] && KeyChanged(key);
}
