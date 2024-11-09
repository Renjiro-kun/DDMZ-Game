#pragma once
#include <raylib/raylib.h>

class FirstPersonCamera
{
public:
    FirstPersonCamera();
    ~FirstPersonCamera() = default;

    Camera& GetCamera() { return m_Camera; }

    void UpdateCamera(float deltaTime);

    Vector3& GetCameraPosition() { return m_Position; }
    Vector3& GetCameraRotation() { return m_Rotation; }
private:
    float m_MovementSpeed = 3.f;
    float m_TurnSpeed = 5000.f;
    Vector3 m_Position{0.f};
    Vector3 m_Rotation{0.f};
    Camera m_Camera;
};