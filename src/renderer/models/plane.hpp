#include "../model.h"

class Plane : public Model
{
    private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    public:
    // clang-format off
    Plane(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
        :position{pos}, rotation{rot}, scale{scale}
    {
        Initialize();
    }
    
    Plane()
        :position{glm::vec3(0.0f)},
        rotation{glm::vec3(0.0f)},
        scale{glm::vec3(1.0f, 1.0f, 0.0f)}
    {
        Initialize();
    }

    // clang-foramt on
    
    private:
    void Initialize()
    {
        shader = Shader("res/shaders/plane.vs", "res/shaders/plane.fs");
        
        std::vector<f32> vertices = {
            // pos          // tex
            -1, 0, 1,  0, 1,
            1, 0, -1,  1, 1,
            1, 0, -1,  1, 0,
            -1, 0, 1,  0, 0

        };

        std::vector<u32> indices = {0, 1, 2, 3};

        Texture texture("res/textures/nri.png", "ground");

        // texture in {} cuz it requires a vector of Textures
        meshes.push_back(Mesh(vertices, indices, {texture}));

        // super function
        // Model::Initialize();
        meshes[0].Setup(shader);
    }

    public:

    void Render()
    {
        LOGINIT_COUT();
        shader.Bind();
        
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        
        model = glm::scale(model, scale);
        model = glm::translate(model, position);

        shader.Bind();
        shader.SetUniformMat4f("model", model);

        // super function
        Model::Render();
    }

};