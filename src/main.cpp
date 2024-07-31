#include "core/defines.h"
#include "core/logger.h"
#include "core/window.h"

#include "renderer/vertexBuffer.h"
#include "renderer/indexBuffer.h"
#include "renderer/vertexArray.h"

#include "renderer/shader.h"
#include "renderer/texture.h"

#include "renderer/renderer.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include <iostream>

#include "../thirdparty/include/glm/glm.hpp"
#include "../thirdparty/include/glm/gtc/matrix_transform.hpp"

#include "tests/testClearColor.h"

#define WIN_WIDTH      640
#define WIN_HEIGHT     480
#define WIN_FULLSCREEN false
#define WIN_RESIZEABLE true
#define WIN_V_SYNC     true
#define WIN_TITLE      "DOOM Engine v0.0.1"

#define V_SHADER_PATH "res/shaders/vertShader.glsl"
#define F_SHADER_PATH "res/shaders/fragShader.glsl"
#define TEXTURE_PATH  "res/textures/container.jpg"

// clang-format off
f32 cubeVertices[] = {
    // positions          // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

u32 indices[] = 
{  
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
// clang-format on

// prototypes
void ProcessInput(Window *window);

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

    /// ----------------------- IMGUI INIT --------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init();
    /// ----------------------- IMGUI INIT --------------------

    VertexArray va;
    VertexBuffer vb(cubeVertices, sizeof(cubeVertices));
    // IndexBuffer ib(indices, 6);

    va.Bind();
    vb.Bind();
    // ib.Bind();

    VertexBufferLayout layout;
    // positions
    layout.Push<float>(3);
    // colors NOTE: no colors in cube
    // layout.Push<float>(3);
    // texture coords
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);

    Shader shader(V_SHADER_PATH, F_SHADER_PATH);

    shader.Bind();

    Texture texture(TEXTURE_PATH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Renderer *renderer = new Renderer();

    // wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    test::Test *currentTest = nullptr;
    test::TestMenu *testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->AddTest<test::ClearColor>("Clear Color");

    /// ----------- IMGUI VARS --------------
    f32 rotation[3] = {0.0f, 0.0f, 0.0f};
    f32 pos[3] = {0.0f, 0.0f, -1.8f};

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    while(!window->WindowShouldClose())
    {
        // process input
        ProcessInput(window);
        renderer->Clear(0.2f, 0.1f, 0.3f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();

            ImGui::Begin("TEST MENU");

            if(currentTest != testMenu && ImGui::Button("<"))
            {
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnImGuiRender();
            ImGui::End();
        }

        /// --------------------- MVP Matrices ------------------------
        glm::vec3 rot = glm::vec3(rotation[0], rotation[1], rotation[2]);

        model = glm::rotate(glm::mat4(1.0f), glm::radians(rot[0]), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot[1]), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rot[2]), glm::vec3(0.0f, 0.0f, 1.0f));

        view = glm::translate(glm::mat4(1.0f), glm::vec3(pos[0], pos[1], pos[2]));

        f32 screenRatio = (f32)window->GetWidth() / (f32)window->GetHeight();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), screenRatio, 0.1f, 100.0f);

        shader.SetUniformMat4f("model", model);
        shader.SetUniformMat4f("view", view);
        shader.SetUniformMat4f("proj", proj);

        texture.Bind();
        va.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);
        // renderer->Draw(va, ib, shader);

        // ---------------------- IMGUI WINDOW -------------
        {
            ImGui::Begin("DOOMEngine");
            ImGui::Text("%.1f FPS || %.1fms/frame", io.Framerate, 1000.0f / io.Framerate);
            ImGui::Separator();

            ImGui::Text("Rotate Cube Test");
            ImGui::SliderFloat3("rotation", rotation, -90, 90);
            if(ImGui::Button("reset rotation"))
            {
                rotation[0] = 0.0f;
                rotation[1] = 0.0f;
                rotation[2] = 0.0f;
            }
            ImGui::Separator();

            ImGui::Text("Movement Test");
            ImGui::SliderFloat3("movement", pos, -3, 3);
            if(ImGui::Button("reset movement"))
            {
                pos[0] = 0.0f;
                pos[1] = 0.0f;
                pos[2] = -1.8f;
            }
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window->GetWindow());
    }

    if(currentTest != testMenu)
    {
        delete currentTest;
        delete testMenu;
    }
    else
    {
        delete currentTest;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete window;
}

void ProcessInput(Window *window)
{
    // if ESC is pressed exit
    if(Keyboard::GetKey(GLFW_KEY_ESCAPE))
        window->SetWindowShouldClose(true);

    // update joystick input
    window->UpdateJoystick();
}