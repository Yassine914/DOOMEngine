#pragma once

#include "../core/defines.h"

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

#include "shader.h"

class Renderer
{
    public:
    Renderer() { glEnable(GL_DEPTH_TEST); }

    inline void Clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    inline void Clear(f32 r, f32 g, f32 b, f32 a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};
