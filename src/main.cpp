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

    /// ----------------------- IMGUI INIT --------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init();
    /// ----------------------- IMGUI INIT --------------------

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

    // model view projection matrices.
    // move everything to the left to
    // create the illusion of moving the "camera" right.
    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

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

    glm::vec3 translate(0, 0, 0);

    while(!window->WindowShouldClose())
    {
        renderer->Clear(0.2f, 0.1f, 0.3f, 1.0f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if(currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();

            ImGui::Begin("Test: ");

            if(currentTest != testMenu && ImGui::Button("<"))
            {
                delete currentTest;
                currentTest = testMenu;
            }

            currentTest->OnImGuiRender();
            ImGui::End();
        }

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translate);

        // matrices are right multiplicative.
        // first mult Vec3(pos) with model -> view -> projection
        glm::mat4 mvp = proj * view * model;
        shader.SetUniformMat4f("MVPMat", mvp);

        // TODO: handle input

        texture.Bind();
        renderer->Draw(va, ib, shader);

        // ---------------------- IMGUI WINDOW -------------
        {
            ImGui::Begin("DOOMEngine Info");
            ImGui::Text("%.1f FPS || %.1fms/frame", io.Framerate, 1000.0f / io.Framerate);
            ImGui::SliderFloat2("translate", &translate.x, -1.0f, 1.0f);

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window->GetWindow());
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete window;
}