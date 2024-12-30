#include <Defines.h>
#include <Scene/ScenesImpl/SceneTitle.h>

#include <Scene/SceneManager.h>
#include <Scene/ScenesImpl/SceneMainMenu.h>
#include <Input/InputContextManager.h>

#include <UI/Button.h>
#include <VMU/SaveManager.h>

void SceneTitle::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_AdvFont = LoadFont(GET_ASSET_FROM_RD("font_adv.png"));
    m_EarthTexture = LoadTexture(GET_ASSET_FROM_CD("titlescreen/BG_Earth.png"));

    m_AdvTextures = new Texture2D[widthCount * heightCount];
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
            m_AdvTextures[y*widthCount+x] = LoadTexture(TextFormat(GET_ASSET_FROM_CD("titlescreen/BG_TS_%01i%01i.png"), y+1, x+1));
        }
    }

    SaveGameManager::GetInstance().LoadData();
}

void SceneTitle::OnDectivated()
{
    for (size_t i = 0; i < heightCount * widthCount; i++)
    {
        UnloadTexture(m_AdvTextures[i]);
    }
    UnloadFont(m_AdvFont);
    UnloadTexture(m_EarthTexture);
    delete[] m_AdvTextures;
}

void SceneTitle::OnDraw3D()
{

}

void SceneTitle::OnDraw2D()
{
    
#ifdef DEBUG
    DrawText(TextFormat("%i", SaveGameManager::GetInstance().GetPlayerPositionY()), 20, 20, 20, GREEN);
#endif
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
           DrawTexture(m_AdvTextures[y*widthCount+x], x * 256, y * 256, WHITE);
        }
    }
    DrawTextureEx(m_EarthTexture, Vector2{128, HEIGHT-128}, 0, 2.f, WHITE);
    DrawTextEx(m_AdvFont, "PRESS START", Vector2{ 200, HEIGHT-150 }, 32, 1, Fade(WHITE, fabs(sin(GetTime()*1.5f))));
}

void SceneTitle::OnUpdate()
{
    if(IsGamepadAvailable(0) && InputContextManager::GetInstance().CurrentInputComtext() == InputContext::Default)
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {   
            SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAIN_MENU);
        }
    }
}