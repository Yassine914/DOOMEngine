#include "core/defines.h"
#include "core/logger.h"

#include "mesh2.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model2
{
    public:
    std::vector<Mesh2> meshes;

    public:
    Model2() {}

    virtual void Initialize() {}

    virtual void Render(Shader &shader)
    {
        for(Mesh2 mesh : meshes)
            mesh.Render(shader);
    }

    virtual void Cleanup()
    {
        for(Mesh2 mesh : meshes)
            mesh.Delete();
    }
};