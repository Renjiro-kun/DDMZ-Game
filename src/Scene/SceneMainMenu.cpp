#include "../pch.h"
#include "SceneManager.h"
#include "SceneMainMenu.h"

void SceneMainMenu::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;
}

void SceneMainMenu::OnDectivated()
{

}

void SceneMainMenu::OnDraw3D()
{

}

void SceneMainMenu::OnDraw2D()
{
    DrawText("PRESS START", 200, 50, 20, BLACK);
}

void SceneMainMenu::OnUpdate()
{
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {   
            SceneManager::GetInstance().LoadScene(SCENE_BATTLE);
        }
    }
}