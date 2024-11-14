#include <kos.h>

#include "pch.h"
#include "FirstPersonCamera.h"
#include "Scene/SceneManager.h"


int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);

    SceneManager::GetInstance().Init();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAIN_MENU);

    while (!WindowShouldClose())
    {
        SceneManager::GetInstance().Update();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
                        
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}