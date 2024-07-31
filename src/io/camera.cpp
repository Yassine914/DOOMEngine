#include "camera.h"

// clang-format off

Camera::Camera(glm::vec3 pos)
    :cameraPos{pos}, worldUp{glm::vec3(0.0f, 1.0f, 0.0f)},
     yaw{-90.0f}, pitch{0.0f}, speed{2.5f},
     zoom{45.0f}, cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)}
{
    UpdateCameraVectors();
}

// clang-format on

void Camera::UpdateCameraDir(f64 dx, f64 dy)
{
    yaw += dx;
    pitch += dy;

    pitch = std::clamp(pitch, -89.0f, 89.0f);
}

void Camera::UpdateCameraPos(CameraDirection dir, f64 deltaTime)
{
    f32 velocity = (f64)deltaTime * speed;

    switch(dir)
    {
    case CameraDirection::FORWARD:
        cameraPos += cameraFront * velocity;
        break;
    case CameraDirection::BACKWARD:
        cameraPos -= cameraFront * velocity;
        break;
    case CameraDirection::RIGHT:
        cameraPos += cameraRight * velocity;
        break;
    case CameraDirection::LEFT:
        cameraPos -= cameraRight * velocity;
        break;
    case CameraDirection::UP:
        cameraPos += cameraUp * velocity;
        break;
    case CameraDirection::DOWN:
        cameraPos -= cameraUp * velocity;
        break;
    case CameraDirection::NONE:
        break;
    }
}

void Camera::UpdateCameraZoom(f64 dy)
{
    zoom -= dy;
    zoom = std::clamp(zoom, 1.0f, 45.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::UpdateCameraVectors()
{
    f32 yawRad = glm::radians(yaw);
    f32 pitchRad = glm::radians(pitch);

    glm::vec3 direction;
    direction.x = cos(yawRad) * cos(pitchRad);
    direction.y = cos(pitchRad);
    direction.z = sin(yawRad) * cos(pitchRad);

    cameraFront = glm::normalize(direction);

    // cross product of cameraFront and worldUp normalized
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));

    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

Camera::~Camera() {}
