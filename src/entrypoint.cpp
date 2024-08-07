#include "core/logger.h"

#include "core/window.h"
#include <GLFW/glfw3.h>

#include <Eigen/Dense>

int main()
{
    LOGINIT_COUT();
    Log(LOG_INFO) << "welcome to DOOMalsdkfj Engine\n";

    Window *window = new Window;

    Log(LOG_INFO) << "window initialized\n";

    window->InitializeWindow();
    Log(LOG_INFO) << "window initialized\n";

    while(!window->WindowShouldClose())
    {
        Log(LOG_INFO) << "window loop\n";
        glfwPollEvents();
    }

    Log(LOG_INFO) << "application loop exited\n";

    delete window;
}