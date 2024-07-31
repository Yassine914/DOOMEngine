#include "joystick.h"

Joystick::Joystick(i32 i)
{
    ID = GetID(i);

    Update();
}

void Joystick::Update()
{
    present = glfwJoystickPresent(ID);

    if(present)
    {
        name = glfwGetJoystickName(ID);
        axes = glfwGetJoystickAxes(ID, &axesCount);
        buttons = glfwGetJoystickButtons(ID, &buttonCount);
    }
}

f32 Joystick::GetAxesState(i32 axis)
{
    if(present)
        return axes[axis];

    return 0.0f;
}

u8 Joystick::GetButtonState(i32 button)
{
    return present ? buttons[button] : GLFW_RELEASE;
}

i32 Joystick::GetAxesCount()
{
    return axesCount;
}

i32 Joystick::GetButtonCount()
{
    return buttonCount;
}

bool Joystick::IsPresent()
{
    return present;
}

std::string Joystick::GetName()
{
    return name;
}

i32 Joystick::GetID(i32 i)
{
    return GLFW_JOYSTICK_1 + i;
}