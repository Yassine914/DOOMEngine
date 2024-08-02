#include "core/defines.h"
#include "core/logger.h"
#include "core/window.h"

#include "renderer/vertexBuffer.h"
#include "renderer/indexBuffer.h"
#include "renderer/vertexArray.h"

#include "renderer/shader.h"
#include "renderer/texture.h"

#include "renderer/renderer.h"

#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/joystick.h"
#include "io/camera.h"

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
void ProcessInput(Window *window, f32 deltaTime);

// globals
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));

LOGINIT_COUT();

int main()
{
    f32 deltaTime = 0.0f;
    f32 lastFrame = 0.0f;

    // initialize window
    Window *window = new Window();

    window->SetWindowSize(WIN_WIDTH, WIN_HEIGHT);
    window->SetFullscreen(WIN_FULLSCREEN);
    window->SetResizeable(WIN_RESIZEABLE);
    window->SetVSync(WIN_V_SYNC);
    window->SetWindowTitle(WIN_TITLE);

    window->InitializeWindow();

    // NOTE: will remove cursor
    //

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

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    while(!window->WindowShouldClose())
    {
        // calculate delta time
        f64 currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;

        // process input
        ProcessInput(window, deltaTime);
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

        view = camera->GetViewMatrix();

        f32 screenRatio = (f32)window->GetWidth() / (f32)window->GetHeight();
        glm::mat4 proj = glm::perspective(glm::radians(camera->zoom), screenRatio, 0.1f, 100.0f);

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

    delete camera;
    delete window;
}

void ProcessInput(Window *window, f32 deltaTime)
{
    // if ESC is pressed exit
    if(Keyboard::GetKey(GLFW_KEY_ESCAPE))
        window->SetWindowShouldClose(true);

    // update joystick input
    window->UpdateJoystick();

    /// -------------- CAMERA INPUT --------------------
    if(Keyboard::GetKey(GLFW_KEY_W))
        camera->UpdateCameraPos(CameraDirection::FORWARD, deltaTime);

    if(Keyboard::GetKey(GLFW_KEY_S))
        camera->UpdateCameraPos(CameraDirection::BACKWARD, deltaTime);

    if(Keyboard::GetKey(GLFW_KEY_A))
        camera->UpdateCameraPos(CameraDirection::LEFT, deltaTime);

    if(Keyboard::GetKey(GLFW_KEY_D))
        camera->UpdateCameraPos(CameraDirection::RIGHT, deltaTime);

    if(Keyboard::GetKey(GLFW_KEY_SPACE))
        camera->UpdateCameraPos(CameraDirection::UP, deltaTime);

    if(Keyboard::GetKey(GLFW_KEY_LEFT_SHIFT))
        camera->UpdateCameraPos(CameraDirection::DOWN, deltaTime);

    // process mouse movement to rotate camera
    f64 dx = Mouse::GetDX(), dy = Mouse::GetDY();
    const f64 sensitivity = 0.5;
    dx *= sensitivity;
    dy *= sensitivity;

    if(Mouse::GetButton(GLFW_MOUSE_BUTTON_2) && (dx != 0 || dy != 0))
    {
        camera->UpdateCameraDir(dx, dy);
    }

    // hide cursor while holding RMB
    if(Mouse::GetButtonDown(GLFW_MOUSE_BUTTON_2))
        window->DisableCursor();
    else if(Mouse::GetButtonUp(GLFW_MOUSE_BUTTON_2))
        window->EnableCursor();

    f64 scrollDY = Mouse::GetScrollDY();
    if(scrollDY != 0)
        camera->UpdateCameraZoom(scrollDY);
}