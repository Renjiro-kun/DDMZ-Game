#include <Defines.h>
#include <Scene/ScenesImpl/SceneCredits.h>
#include <Scene/SceneManager.h>

#include <dc/syscalls.h>

void SceneCredits::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;
}

void SceneCredits::OnDectivated()
{
}

void SceneCredits::OnDraw3D()
{

}

void SceneCredits::OnDraw2D()
{
    DrawText(m_CreditsString[m_CurrentText].c_str(), WIDTH/2, HEIGHT/2, 30, Fade(WHITE, m_Alpha));
}

void SceneCredits::OnUpdate()
{
    if (m_State == 0)
    {
        m_Alpha += 0.009f;

        if(m_Alpha >= 1.f)
        {
            m_Alpha = 1.f;
            m_State++;
        }
    }
    else if(m_State == 1)
    {
        m_Alpha -= 0.009f;

        if(m_Alpha <= 0.f)
        {
            m_Alpha = 0.f;
            m_State++;
            m_CurrentText++;
        }
    }
    if (m_State == 2)
    {
        m_Alpha += 0.009f;

        if(m_Alpha >= 1.f)
        {
            m_Alpha = 1.f;
            m_State++;
        }
    }
    else if(m_State == 3)
    {
        m_Alpha -= 0.009f;

        if(m_Alpha <= 0.f)
        {
            m_Alpha = 0.f;
            m_State++;
        }
    }
    else if(m_State == 4)
    {
        ExitScene();
    }

    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {   
            ExitScene();
        }
    }
}

void SceneCredits::ExitScene()
{
    syscall_system_bios_menu();
}