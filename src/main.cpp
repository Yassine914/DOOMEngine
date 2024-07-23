#include "core/window.h"
#include "core/shader.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_FULLSCREEN false
#define WIN_RESIZEABLE true
#define WIN_V_SYNC true
#define WIN_TITLE "DOOM Engine v0.0.1"

// TODO: get relative shader path
#define V_SHADER_PATH "G:/Projects/CodeProjects/DOOMEngine/resources/shaders/fragShader.glsl"
#define F_SHADER_PATH "G:/Projects/CodeProjects/DOOMEngine/resources/shaders/vertShader.glsl"

int main()
{
    // initialize window
    Window *window = new Window();

    window->SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
    window->SetFullscreen(WIN_FULLSCREEN);
    window->SetResizeable(WIN_RESIZEABLE);
    window->SetVSync(WIN_V_SYNC);
    window->SetWindowTitle(WIN_TITLE);

    window->InitializeWindow();

    // main game loop
    window->Run();

    delete window;
}