#include "../include/renderer.h"
#include "../include/window.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_FULLSCREEN false
#define WIN_RESIZEABLE true
#define WIN_TITLE "DOOM Engine v0.0.1"

#define V_SYNC true
#define V_SHADER_PATH "./shaders/vertShader.glsl"
#define F_SHADER_PATH "./shaders/fragShader.glsl"

using namespace win;

int main(int argc, char **argv)
{
    // initialize window
    Window *window = new Window();

    window->SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
    window->SetFullscreen(WIN_FULLSCREEN);
    window->SetResizeable(WIN_RESIZEABLE);
    window->SetWindowTitle(WIN_TITLE);

    window->InitializeWindow();
    // main game loop
    window->Run();

    delete window;
    return 0;

    // TODO: link OpenGL with GLFW
    //  initialize renderer
    Renderer *renderer = new Renderer();

    renderer->SetVSync(V_SYNC);

    // initialize shaders
    renderer->SetVShaderPath(V_SHADER_PATH);
    renderer->SetFShaderPath(F_SHADER_PATH);
    renderer->InitializeShaders();

    delete renderer;
}