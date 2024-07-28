#include "test.h"

namespace test {

// clang-format off
TestMenu::TestMenu(Test *&currentTestPtr)
    :currentTest{currentTestPtr}
{
}

void TestMenu::OnImGuiRender()
{
    for(auto &[testName, testFunc] : tests)
    {
        if(ImGui::Button(testName.c_str())) 
            currentTest = testFunc();
    }
}
// clang-format on

} // namespace test