#include "pch.h"
#include "FirstPersonCamera.h"
#include <PuruPuruManager.h>
#include <Messages/MessageManager.h>
#include <Input/InputContextManager.h>

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
    if(IsGamepadAvailable(0) && InputContextManager::GetInstance().CurrentInputComtext() == InputContext::Default)
    {
        float movement = -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float turn = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);

        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {
            SFXManager::GetInstance().Play(m_BoomSFX);
            PuruPuruManager::GetInstance().Rumble(0x3339F010);
        }

        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
        {
            MessageManager::GetInstance().Request();
        }

        Vector3 desiredPosition = Vector3{movement * m_MovementSpeed * deltaTime, 0.f, 0.f };
        Vector3 desiredRotation = Vector3{turn * DEG2RAD * m_TurnSpeed * deltaTime, 0.f, 0.f};

        UpdateCameraPro(&m_Camera, desiredPosition, desiredRotation, 0.f);
    }   
}