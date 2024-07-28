#pragma once

#include "../core/defines.h"

#include <vector>
#include <string>
#include <functional>

#include "../vendor/imgui/imgui.h"

namespace test {

class Test
{
    public:
    Test() {}

    virtual void OnUpdate(f32 deltaTime) {}
    virtual void OnRender() {}

    virtual void OnImGuiRender() {}

    virtual ~Test() {}
};

// clang-format off

class TestMenu : public Test
{
    private:
    Test *&currentTest; // ref to a test ptr
    std::vector<std::pair<std::string, std::function<Test *()>>> tests;

    public:
    TestMenu(Test *&currentTestPtr);

    template<typename T>
    void AddTest(const std::string &name)
    {
        tests.push_back(std::make_pair(name, []() { return new T(); }));
    }

    virtual void OnImGuiRender() override;

    virtual ~TestMenu() override {}
};

// clang-format on

} // namespace test