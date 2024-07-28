#pragma once

#include "test.h"

namespace test {

class ClearColor : public Test
{
    private:
    f32 clearColor[4];

    public:
    ClearColor();

    void OnUpdate(f32 deltaTime) override;
    void OnRender() override;

    void OnImGuiRender() override;

    ~ClearColor();
};

} // namespace test