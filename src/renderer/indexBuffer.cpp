#include "indexBuffer.h"

IndexBuffer::IndexBuffer() {}

IndexBuffer::IndexBuffer(const u32 *data, u32 count) : count{count}
{
    Initialize(data, count);
}

void IndexBuffer::Initialize(const u32 *data, u32 count)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}