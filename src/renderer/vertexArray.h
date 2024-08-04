#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray
{
    private:
    u32 ID;

    public:
    VertexArray();

    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

    inline void Bind() const { glBindVertexArray(ID); }
    void Unbind() const;

    inline void Delete() { glDeleteVertexArrays(1, &ID); }

    ~VertexArray();
};