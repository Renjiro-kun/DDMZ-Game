#pragma once
#include <raylib/raylib.h>
#include <Sound/SfxManager.h>

class FirstPersonCamera
{
public:
    FirstPersonCamera();
    ~FirstPersonCamera() = default;

    void OnActivate();
    void OnDeactivate();

    Camera& GetCamera() { return m_Camera; }

    void UpdateCamera(float deltaTime);

    Vector3 GetPosition() const { return m_Camera.position; }
    void SetPosition(Vector3 position) { m_Camera.position = position; }

    void OnDraw2D();

    Vector3 GetForwardVector();
    Vector3 GetRightVector();
    Vector3 GetUpVector();

    bool IsInDrawingRange(const Vector3& position);

    void SetCullingDistance(float value) {m_CullingDistance = value;}
private:
    const float STEP_TIMING = 0.3f;
    float m_CullingDistance = 5.f;

    SFXHandle m_StepSFX;
    float m_MovementSpeed = 3.f;
    float m_TurnSpeed = 5000.f;
    Camera m_Camera;

    float m_StepTimer = 0.f;
};