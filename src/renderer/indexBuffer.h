#pragma once

#include "../core/defines.h"
#include "../../thirdparty/include/glad/glad.h"

#include <vector>

class IndexBuffer
{
    private:
    u32 ID;
    u32 count; // vertices count

    public:
    IndexBuffer();
    IndexBuffer(const u32 *data, u32 count);

    void Initialize(const u32 *data, u32 count);

    void Bind() const;
    void Unbind() const;

    inline u32 GetCount() const { return count; }

    ~IndexBuffer();
};
