#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, u32 size)
{
    glGenBuffers(1, &rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::MakeActive() const
{

    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::MakeInactive() const
{

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &rendererID);
}