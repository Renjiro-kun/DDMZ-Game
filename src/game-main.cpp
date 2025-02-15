#include <kos.h>

#include <Defines.h>

#include <Gameplay/Inventory/InventoryManager.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <Gameplay/TimerController.h>
#include <Input/InputContextManager.h>
#include <Messages/MessageManager.h>
#include <Scene/SceneManager.h>
#include <Sound/BgmManager.h>
#include <Sound/SfxManager.h>
#include <VMU/SaveManager.h>
#include <VMU/PuruPuruManager.h>
#include <VMU/vmu_profiler.h>
#include <UI/UIRepository.h>

#include <dc/syscalls.h>

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);
    InputContextManager::GetInstance().Init();
    MessageManager::GetInstance().Init();
    SaveGameManager::GetInstance().Init();

    BGMManager::GetInstance().Init();
    SFXManager::GetInstance().Init();
    UIRepository::GetInstance().Init();

    PuruPuruManager::GetInstance().Init();

    SceneManager::GetInstance().Init();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_INTRO);
    ObjectRepository::GetInstance().Init();
    InventoryManager::GetInstance().Init();
    TimerController::GetInstance().Init();
#if DEBUG
    VmuProfiler prof;
#endif
    while (!WindowShouldClose())
    {
        SceneManager::GetInstance().Update();
        MessageManager::GetInstance().Update();
        TimerController::GetInstance().Update();

        BeginDrawing();
            SceneManager::GetInstance().ClearScreen();
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
            MessageManager::GetInstance().OnDraw2D();
            TimerController::GetInstance().OnDraw2D();
#ifdef DEBUG
            DrawFPS(10, 10);
            prof.setVertexCount(0);
#endif
        EndDrawing();
    }

    TimerController::GetInstance().Shutdown();
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
    syscall_system_bios_menu();

    return 0;
}