#include "vertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &ID);
}

VertexBuffer::VertexBuffer(const void *data, u32 size)
{
    glGenBuffers(1, &ID);
    Initialize(data, size);
}

void VertexBuffer::Initialize(const void *data, u32 size)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Unbind() const
{

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}