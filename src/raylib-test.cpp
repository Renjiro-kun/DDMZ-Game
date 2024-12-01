#include <kos.h>

#include "pch.h"
#include <FirstPersonCamera.h>
#include <Scene/SceneManager.h>

#include <Sound/BgmManager.h>
#include <Sound/SfxManager.h>

#include <Input/InputContextManager.h>

#include <Messages/MessageManager.h>

#include <PuruPuruManager.h>

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);

    BGMManager::GetInstance().Init();
    SFXManager::GetInstance().Init();

    PuruPuruManager::GetInstance().Init();
    InputContextManager::GetInstance().Init();

    SceneManager::GetInstance().Init();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_INTRO);
    MessageManager::GetInstance().Init();

    while (!WindowShouldClose())
    {
        SceneManager::GetInstance().Update();
        MessageManager::GetInstance().Update();

        BeginDrawing();
            SceneManager::GetInstance().ClearScreen();
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
            MessageManager::GetInstance().OnDraw2D();
                        
            DrawFPS(10, 10);

        EndDrawing();
    }

    InputContextManager::GetInstance().Shutdown();
    MessageManager::GetInstance().Shutdown();
    PuruPuruManager::GetInstance().Shutdown();
    SFXManager::GetInstance().Shutdown();
    BGMManager::GetInstance().Shutdown();

    CloseWindow();
    return 0;
}