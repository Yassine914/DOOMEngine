#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "../../thirdparty/include/glad/glad.h"
#include <GLFW/glfw3.h>

class Renderer
{
    public:
    Renderer() { glEnable(GL_DEPTH_TEST); }

    inline void Clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    inline void Clear(f32 r, f32 g, f32 b, f32 a) const
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    inline void EnableBlending() const
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    inline void RenderAllWireframe() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
};

bool CheckOpenGLError();