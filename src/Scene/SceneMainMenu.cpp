#include "../pch.h"
#include "SceneManager.h"
#include "SceneMainMenu.h"

void SceneMainMenu::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_AdvTextures = new Texture2D[widthCount * heightCount];
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
            m_AdvTextures[y*widthCount+x] = LoadTexture(TextFormat("/cd/titlescreen/ts%01i%01i.png", y+1, x+1));
        }
    }
    
}

void SceneMainMenu::OnDectivated()
{
    for (size_t i = 0; i < heightCount * widthCount; i++)
    {
        UnloadTexture(m_AdvTextures[i]);
    }
    delete[] m_AdvTextures;
}

void SceneMainMenu::OnDraw3D()
{

}

void SceneMainMenu::OnDraw2D()
{
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
           DrawTexture(m_AdvTextures[y*widthCount+x], x * 256, y * 256, WHITE);
        }
    }
    DrawText("PRESS START", 200, 50, 20, BLACK);
}

void SceneMainMenu::OnUpdate()
{
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {   
            SceneManager::GetInstance().LoadScene(SCENE_MAZE);
        }
    }
}