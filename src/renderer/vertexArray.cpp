#include "vertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();

    // clang-format off
    const auto &elements = layout.GetElements();
    u32 offset = 0;
    for(u32 i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, 
            element.count, 
            element.type, 
            element.normalized,
            layout.GetStride(),
            (const void *) (u64) offset);
        
        offset += element.count * LayoutElement::GetSizeOfType(element.type);
    }

    // clang-format on
}

void VertexArray::Bind() const
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}
