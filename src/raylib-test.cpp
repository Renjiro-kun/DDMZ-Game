#include <kos.h>

#include <Defines.h>
#include <FirstPersonCamera.h>
#include <Scene/SceneManager.h>
#include <UI/UIRepository.h>

#include <Sound/BgmManager.h>
#include <Sound/SfxManager.h>

#include <Input/InputContextManager.h>

#include <Messages/MessageManager.h>
#include <VMU/SaveManager.h>
#include <PuruPuruManager.h>

#include <Gameplay/Inventory/InventoryManager.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <VMU/vmu_profiler.h>

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
    ObjectRepository::GetInstance().Init();
    InventoryManager::GetInstance().Init();
    VmuProfiler prof;

    while (!WindowShouldClose())
    {
        SceneManager::GetInstance().Update();
        MessageManager::GetInstance().Update();

        BeginDrawing();
            SceneManager::GetInstance().ClearScreen();
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
            MessageManager::GetInstance().OnDraw2D();
#ifdef DEBUG
            DrawFPS(10, 10);
            prof.setVertexCount(0);
#endif
        EndDrawing();
    }

    InventoryManager::GetInstance().Shutdown();
    ObjectRepository::GetInstance().Shutdown();
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