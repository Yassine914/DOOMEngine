#pragma once

#include "../core/defines.h"

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

class Renderer
{
    private:
    f32 clearColor[4];

    public:
    // clang-format off
    Renderer()
        :clearColor{0.2f, 0.1f, 0.3f, 1.0f}
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    // clang-format on

    inline void SetClearColor(f32 r, f32 g, f32 b, f32 a)
    {
        clearColor[0] = r;
        clearColor[1] = g;
        clearColor[2] = b;
        clearColor[3] = a;
    }

    inline void NewFrame()
    {
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void RenderAsWireFrame() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
