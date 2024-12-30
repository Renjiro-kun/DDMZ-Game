#include <Defines.h>
#include <Gameplay/FirstPersonCamera.h>
#include <VMU/PuruPuruManager.h>
#include <Messages/MessageManager.h>
#include <Input/InputContextManager.h>
#include <raylib/raymath.h>

FirstPersonCamera::FirstPersonCamera()
{
    m_Camera.position = (Vector3){.2f, 0.4f, .2f};
    m_Camera.target = (Vector3){0185.f, 0.4f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.0f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

}

void FirstPersonCamera::OnActivate()
{
    m_StepSFX = SFXManager::GetInstance().LoadSFX(GET_ASSET_FROM_RD("sfx_footstep01.wav"));
}

void FirstPersonCamera::OnDeactivate()
{
    SFXManager::GetInstance().Unload(m_StepSFX);
}

void FirstPersonCamera::UpdateCamera(float deltaTime)
{
    if(IsGamepadAvailable(0) && InputContextManager::GetInstance().CurrentInputComtext() == InputContext::Default)
    {
        float movement = -GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        float turn = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);

        Vector3 desiredPosition = Vector3{movement * m_MovementSpeed * deltaTime, 0.f, 0.f };
        Vector3 desiredRotation = Vector3{turn * DEG2RAD * m_TurnSpeed * deltaTime, 0.f, 0.f};

        if(abs(movement) > 0.1f)
        {
            m_StepTimer += deltaTime;
            if(m_StepTimer > STEP_TIMING)
            {
                SFXManager::GetInstance().Play(m_StepSFX);
                m_StepTimer = 0;
            }
        }

        UpdateCameraPro(&m_Camera, desiredPosition, desiredRotation, 0.f);
    }   
}

Vector3 FirstPersonCamera::GetForwardVector()
{
    return Vector3Normalize(Vector3Subtract(m_Camera.target, m_Camera.position));
}

Vector3 FirstPersonCamera::GetUpVector()
{
    return Vector3Normalize(m_Camera.up);
}

Vector3 FirstPersonCamera::GetRightVector()
{
    Vector3 forward = GetForwardVector();
    Vector3 up = GetUpVector();

    return Vector3CrossProduct(forward, up);
}

constexpr float CULLING_DISTANCE = 5.f;
constexpr float CULLING_DISTANCE_SQ = CULLING_DISTANCE * CULLING_DISTANCE;

bool FirstPersonCamera::IsInDrawingRange(const Vector3& objectPosition)
{

    float dx = abs(objectPosition.x - m_Camera.position.x);
    if(dx > CULLING_DISTANCE) return false;
    float dy = abs(objectPosition.z - m_Camera.position.z);
    if(dy > CULLING_DISTANCE) return false;
    if(dx+dy <= CULLING_DISTANCE) return true;
    return(dx*dx + dy*dy <= CULLING_DISTANCE_SQ);
}

void FirstPersonCamera::OnDraw2D()
{
#ifdef DEBUG
#endif
}