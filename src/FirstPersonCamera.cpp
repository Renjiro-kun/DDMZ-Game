#include "pch.h"
#include "FirstPersonCamera.h"


FirstPersonCamera::FirstPersonCamera()
{
    m_Camera.position = (Vector3){.2f, 0.4f, .2f};
    m_Camera.target = (Vector3){0185.f, 0.4f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.0f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_BoomSFX = SFXManager::GetInstance().LoadSFX("/rd/sfx_boom.wav");
}

void FirstPersonCamera::UpdateCamera(float deltaTime)
{
    if(IsGamepadAvailable(0))
    {
        float movement = -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float turn = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);

        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {
            SFXManager::GetInstance().Play(m_BoomSFX);
        }

        m_Position = Vector3{movement * m_MovementSpeed * deltaTime,0.f, 0.f };
        m_Rotation = Vector3{turn * DEG2RAD * m_TurnSpeed * deltaTime, 0.f, 0.f};

        UpdateCameraPro(&m_Camera, m_Position, m_Rotation, 0.f);
    }   
}