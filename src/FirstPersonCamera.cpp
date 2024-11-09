#include "FirstPersonCamera.h"

#include <dc/maple/controller.h>

FirstPersonCamera::FirstPersonCamera()
{
    m_Camera.position = (Vector3){.2f, 0.4f, .2f};
    m_Camera.target = (Vector3){0185.f, 0.4f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.0f;
    m_Camera.projection = CAMERA_PERSPECTIVE;
}

void FirstPersonCamera::UpdateCamera(float deltaTime)
{
    if(IsGamepadAvailable(0))
    {
        float movement = -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float turn = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);

        if(turn > 0.1f)
        {
            m_Rotation.x = turn * DEG2RAD * m_TurnSpeed * deltaTime;
        }
        if(movement > 0.1f)
        {
            m_Position.x += movement * m_MovementSpeed * deltaTime;
        }
    }
    
    UpdateCameraPro(&m_Camera, m_Position, m_Rotation, 0.f);
}