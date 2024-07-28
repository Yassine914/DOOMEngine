#include "testClearColor.h"

#include <GLFW/glfw3.h>

namespace test {

// clang-format off
ClearColor::ClearColor()
    :clearColor{0.1f, 0.14f, 0.2f, 1.0f}
{

}
// clang-format on

void ClearColor::OnUpdate(f32 deltaTime) {}

void ClearColor::OnRender()
{
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClearColor::OnImGuiRender()
{
    ImGui::ColorEdit4("Clear Color", clearColor);
}

ClearColor::~ClearColor() {}

} // namespace test