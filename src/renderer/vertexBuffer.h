#pragma once

#include "../core/defines.h"
#include "../../thirdparty/include/glad/glad.h"

class VertexBuffer
{
    private:
    u32 rendererID;

    public:
    VertexBuffer(const void *data, u32 size);

    void MakeActive() const;
    void MakeInactive() const;

    ~VertexBuffer();
};