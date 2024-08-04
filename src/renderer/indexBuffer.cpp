#include "indexBuffer.h"

IndexBuffer::IndexBuffer() : initialized{false}
{
    glGenBuffers(1, &ID);
}

IndexBuffer::IndexBuffer(const u32 *data, u32 count) : count{count}
{
    glGenBuffers(1, &ID);
    Initialize(data, count);
}

void IndexBuffer::Initialize(const u32 *data, u32 count)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);

    initialized = true;
}



void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}