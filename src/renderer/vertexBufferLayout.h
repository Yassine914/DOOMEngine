#pragma once

#include "../core/defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <vector>

struct LayoutElement
{
    u32 type;
    u32 count;
    u8 normalized;

    inline static u32 GetSizeOfType(u32 type)
    {
        switch(type)
        {
        case GL_FLOAT:
            return sizeof(f32);
            break;
        case GL_UNSIGNED_INT:
            return sizeof(u32);
            break;
        case GL_UNSIGNED_BYTE:
            return sizeof(u8);
            break;
        }

        return 0;
    }
};

class VertexBufferLayout
{
    private:
    std::vector<LayoutElement> elements;
    u32 stride;

    // clang-format off
    
    public:
    VertexBufferLayout()
        :stride{0} {}
    
    template<typename T> 
    void Push(u32 count)
    {
        static_assert(false);
    }
    
    template<>
    void Push<f32>(u32 count)
    {
        elements.push_back({GL_FLOAT, count, GL_FALSE});
        stride += count * sizeof(f32);
    }

    template<>
    void Push<u32>(u32 count)
    {
        elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        stride += count * sizeof(u32);
    }

    template<>
    void Push<u8>(u32 count)
    {
        elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        stride += count * sizeof(u8);
    }

    // clang-format on
    inline const std::vector<LayoutElement> GetElements() const { return elements; }
    inline u32 GetStride() const { return stride; }
};