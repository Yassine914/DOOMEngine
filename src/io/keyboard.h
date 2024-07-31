#pragma once

#include "../core/defines.h"

#include "../../thirdparty/include/glad/glad.h"
#include <GLFW/glfw3.h>

class Keyboard
{
    private:
    static bool keys[];
    static bool keysChanged[];

    public:
    Keyboard() {}

    // key state callback
    static void KeyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods);

    // getters

    // true if key is pressed
    static bool GetKey(i32 key);

    // changes state of key (pressed-stopped-etc)
    static bool KeyChanged(i32 key);

    // true if the key stopped being pressed
    static bool GetKeyUp(i32 key);

    //  true if key is being held
    static bool GetKeyDown(i32 key);

    ~Keyboard() = default;
};