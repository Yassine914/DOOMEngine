#include "core/window.h"
#include "core/shader.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_FULLSCREEN false
#define WIN_RESIZEABLE true
#define WIN_V_SYNC true
#define WIN_TITLE "DOOM Engine v0.0.1"

// TODO: get relative shader path
#define V_SHADER_PATH "G:/Projects/CodeProjects/DOOMEngine/resources/shaders/vertShader.glsl"
#define F_SHADER_PATH "G:/Projects/CodeProjects/DOOMEngine/resources/shaders/fragShader.glsl"

// clang-format off
f32 vertices[] = 
{
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

u32 indices[] = 
{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
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

    u32 VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    u32 VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    u32 EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), (void *)0);
    glEnableVertexAttribArray(0);

    Shader *vfProgram = new Shader(V_SHADER_PATH, F_SHADER_PATH);

    // main game loop
    // window->Run();
    // TODO: fix main game loop

    while(!glfwWindowShouldClose(window->GetWindow()))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: handle input

        vfProgram->Initialize();
        glBindVertexArray(VAO);

        // NOTE: wireframe mode
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check events and swap buffers
        glfwSwapBuffers(window->GetWindow());
        glfwPollEvents();
    }

    delete window;
}