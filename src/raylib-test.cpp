#include <kos.h>

#include "pch.h"
#include <FirstPersonCamera.h>
#include <Scene/SceneManager.h>

#include <Sound/BgmManager.h>
#include <Sound/SfxManager.h>

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);

    BGMManager::GetInstance().Init();
    SFXManager::GetInstance().Init();

    SceneManager::GetInstance().Init();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAIN_MENU);

    while (!WindowShouldClose())
    {
        SceneManager::GetInstance().Update();

        BeginDrawing();
            SceneManager::GetInstance().ClearScreen();
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
                        
            DrawFPS(10, 10);

        EndDrawing();
    }

    SFXManager::GetInstance().Shutdown();
    BGMManager::GetInstance().Shutdown();

    CloseWindow();
    return 0;
}