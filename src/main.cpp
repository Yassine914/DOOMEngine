#include "core/window.h"

#include "renderer/vertexBuffer.h"
#include "renderer/indexBuffer.h"
#include "renderer/vertexArray.h"

#include "renderer/shader.h"

#include "../thirdparty/include/stb_image.h"
#include <iostream>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_FULLSCREEN false
#define WIN_RESIZEABLE true
#define WIN_V_SYNC true
#define WIN_TITLE "DOOM Engine v0.0.1"

#define V_SHADER_PATH "res/shaders/vertShader.glsl"
#define F_SHADER_PATH "res/shaders/fragShader.glsl"
#define TEXTURE_PATH "res/textures/container.jpg"

// clang-format off
f32 triangle[] = 
{
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

u32 indices[] = 
{  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
// clang-format on

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

    VertexArray va;
    VertexBuffer vb(triangle, 32 * sizeof(f32));
    IndexBuffer ib(indices, 6);

    va.Bind();
    vb.Bind();
    ib.Bind();

    VertexBufferLayout layout;
    // positions
    layout.Push<float>(3);
    // colors
    layout.Push<float>(3);
    // texture coords
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    Shader *shaderProgram = new Shader(V_SHADER_PATH, F_SHADER_PATH);

    // texture test
    i32 width, height, nrChannels;
    u8 *data = stbi_load(TEXTURE_PATH, &width, &height, &nrChannels, 0);

    u32 texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    // since it's only one shader,
    // no need to initialize it every window draw call
    // TODO: fix main game loop
    // window->Run();

    // NOTE: wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while(!window->WindowShouldClose())
    {
        window->SetBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);

        // TODO: handle input

        glBindTexture(GL_TEXTURE_2D, texture);

        shaderProgram->MakeActive();
        va.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // check events and swap buffers
        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete shaderProgram;
    delete window;
}