#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "../../thirdparty/include/glad/glad.h"

class VertexBuffer
{
    private:
    u32 ID;

    public:
    VertexBuffer();
    VertexBuffer(const void *data, u32 size);

    void Initialize(const void *data, u32 size);

    inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, ID); }

    void Unbind() const;

    inline void Delete() { glDeleteBuffers(1, &ID); }

    ~VertexBuffer();
};