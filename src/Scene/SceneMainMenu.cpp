#include <pch.h>
#include <Scene/SceneManager.h>
#include <Scene/SceneMainMenu.h>

#include <UI/Button.h>

void SceneMainMenu::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_AdvFont = LoadFont("/rd/font_adv.png");

    m_MenuCanvas = new Canvas();
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 200}));
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 250}));


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
    UnloadFont(m_AdvFont);
    delete[] m_AdvTextures;
    delete m_MenuCanvas;
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
    DrawTextEx(m_AdvFont, "PRESS START", Vector2{ 200, 50 }, 32, 1, BLACK);

    m_MenuCanvas->OnDraw2D();
}

void SceneMainMenu::OnUpdate()
{
    m_MenuCanvas->OnUpdate();
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {   
            SceneManager::GetInstance().LoadScene(SCENE_MAZE);
        }
    }
}