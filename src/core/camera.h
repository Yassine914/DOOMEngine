#pragma once

#include "defines.h"

#include "../input/mouse.h"
#include "../input/keyboard.h"
#include "../input/joystick.h"

#include "../../thirdparty/include/glm/glm.hpp"
#include "../../thirdparty/include/glm/gtc/matrix_transform.hpp"

enum class CameraDirection
{
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
    public:
    glm::vec3 cameraPos;

    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::vec3 worldUp;

    f32 yaw, pitch;
    f32 speed;
    f32 zoom; // field of view

    public:
    Camera(glm::vec3 pos);

    /// -------------- UPDATES ----------------
    // rotate camera based on mouse movement (dx, dy)
    void UpdateCameraDir(f64 dx, f64 dy);

    // move depending on enum value
    void UpdateCameraPos(CameraDirection dir, f64 deltaTime);

    // change zoom depending on scroll wheel
    void UpdateCameraZoom(f64 dy);

    /// -------------- GETTERS ----------------
    glm::mat4 GetViewMatrix();

    ~Camera();

    private:
    void UpdateCameraVectors();
};