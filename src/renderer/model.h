#pragma once

#include "../core/defines.h"
#include "../core/logger.h"

#include "../../thirdparty/include/glad/glad.h"

#include "../../thirdparty/include/glm/glm.hpp"
#include "../../thirdparty/include/glm/gtc/matrix_transform.hpp"

#include <vector>

#include "mesh.h"

class Model
{
    private:
    public:
    std::vector<Mesh> meshes;

    public:
    Model();

    void Initialize();

    void Render(Shader shader)
    {
        for(Mesh mesh : meshes)
        {
            mesh.Render(shader);
        }
    }

    void Cleanup()
    {
        for(Mesh mesh : meshes)
        {
            mesh.Cleanup();
        }
    }

    ~Model();
};