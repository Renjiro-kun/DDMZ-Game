#include <pch.h>
#include <Messages/MessageManager.h>
#include <Input/InputContextManager.h>

void MessageManager::Init()
{
    m_DialogBoxTextures = new Texture2D[DIALOGBOX_TILES];
    for (size_t i = 0; i < DIALOGBOX_TILES; i++)
    {
        m_DialogBoxTextures[i] = LoadTexture(TextFormat("/rd/dlgbox%0i.png", i+1));
    }
}

void MessageManager::Shutdown()
{
    m_DialogRequested = false;
    for (size_t i = 0; i < DIALOGBOX_TILES; i++)
    {
        UnloadTexture(m_DialogBoxTextures[i]);
    }
    delete[] m_DialogBoxTextures;
}

void MessageManager::OnDraw2D()
{
    if(m_DialogRequested)
    {
        for (size_t i = 0; i < DIALOGBOX_TILES; i++)
        {
            DrawTexture(m_DialogBoxTextures[i], i * 256, 256, WHITE);
        }
        DrawText("Test message", 0, 256, 32, WHITE);
    }
}

void MessageManager::Request()
{
    if(!m_DialogRequested)
    {
        m_DialogRequested = true;
        InputContextManager::GetInstance().SetInputContext(InputContext::Message);
    }
}

void MessageManager::Update()
{
    if(IsGamepadAvailable(0) && InputContextManager::GetInstance().CurrentInputComtext() == InputContext::Message)
    {
        if(m_DialogRequested && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
        {
            m_DialogRequested = false;
            InputContextManager::GetInstance().SetInputContext(InputContext::Default);
        }
    }
}