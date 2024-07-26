#pragma once

#include "../core/defines.h"

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
    private:
    u32 rendererID;

    public:
    VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    void Bind() const;
    void Unbind() const;

    ~VertexArray();
};