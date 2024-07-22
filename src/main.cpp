/*
#include "../include/mats.h"
#include "../include/utils.h"

using namespace std;
using namespace renderer;

// data is first sent down the pipeline in buffers, which is then organized into VAOs
#define numVAOs 2 // num of vertex array objects

GLuint renderingProgram; // GLuint is unsigned int specific to OpenGL
GLuint vao[numVAOs];

void display(GLFWwindow *window, double currentTime);

void OnWindowResize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Init(GLFWwindow *window)
{
    // Creating the shader programs and Generating Vertices
    renderingProgram = CreateShaderProgram(); // returns vfProgram (ID to the OpenGL program)
    glGenVertexArrays(numVAOs, vao);          // create VAOs required for using shaders
    glBindVertexArray(vao[0]);
}

int main()
{
    if(!glfwInit()) // Init GLFW
    {
        ErrorCallback(1, "Failed to Init GLFW");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // specify req of OpenGL v4.6 support
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwSetErrorCallback(ErrorCallback);

    // Create Winow
    GLFWwindow *window = glfwCreateWindow(640, 480, "DOOM engine v0.01", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // create an OpenGL context

    // Load OpenGL 4.6 using GLAD
    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(version == 0)
    {
        ErrorCallback(2, "Failed to Init OpenGL");
        return 2;
    }
    glfwSwapInterval(1); // for vsync

    // load the frame buffer size callback after
    // loading OpenGL
    glfwSetFramebufferSizeCallback(window, OnWindowResize);

    Init(window); // init shaders

    // Application loop
    while(!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window); // update screen
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

float x = 0.0f;                              // location of triangle on x axis
float y = 0.0f;                              // location of triangle on y axis
float xInc = !(rand() % 2) ? 0.01f : -0.01f; // offset for moving the triangle
float yInc = !(rand() % 2) ? 0.02f : -0.02f; // random offset

void display(GLFWwindow *window, double currentTime)
{
    // clearing depth and color buffer to init hidden surface removal
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); // reset background every call(avoid extension of triangle)

    // Render Point
    glUseProgram(renderingProgram); // loads program in the OpenGL pipeline stages (onto GPU)

    x += xInc; // add offset amount per frame to x and y
    y += yInc;

    if(x >= 1.0f) xInc = -0.01f;
    if(x <= -1.0f) xInc = 0.01f;
    if(y >= 1.0f) yInc = -0.01f;
    if(y <= -1.0f) yInc = 0.01f;

    GLuint xOffset = glGetUniformLocation(renderingProgram, "xOffset"); // get ptr to offset(var in shader code)
    glProgramUniform1f(renderingProgram, xOffset, x);                   // set value of x in offset

    GLuint yOffset = glGetUniformLocation(renderingProgram, "yOffset"); // get ptr to offset(var in shader code)
    glProgramUniform1f(renderingProgram, yOffset, y);                   // set value of x in offset

    glDrawArrays(GL_TRIANGLES, 0, 3); // initiates pipeline processing
    glPointSize(30.0f);
    glDrawArrays(GL_POINT, 1, 1);
}
*/