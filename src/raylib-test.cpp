#include <kos.h>

#include "pch.h"
#include <FirstPersonCamera.h>
#include <Scene/SceneManager.h>
#include <UI/UIRepository.h>

#include <Sound/BgmManager.h>
#include <Sound/SfxManager.h>

#include <Input/InputContextManager.h>

#include <Messages/MessageManager.h>
#include <VMU/SaveManager.h>
#include <PuruPuruManager.h>

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);
    InputContextManager::GetInstance().Init();
    MessageManager::GetInstance().Init();
    
    SaveGameManager::GetInstance().Init();
    UIRepository::GetInstance().Init();

    BGMManager::GetInstance().Init();
    SFXManager::GetInstance().Init();

    PuruPuruManager::GetInstance().Init();

    SceneManager::GetInstance().Init();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_INTRO);

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
    UIRepository::GetInstance().Shutdown();
    PuruPuruManager::GetInstance().Shutdown();
    SFXManager::GetInstance().Shutdown();
    BGMManager::GetInstance().Shutdown();
    SaveGameManager::GetInstance().Shutdown();
    CloseWindow();
    return 0;
}