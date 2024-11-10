#include <kos.h>

#include "pch.h"
#include "FirstPersonCamera.h"
#include "Scene/SceneManager.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);

    SceneManager::GetInstance().Init();

    float joyX = 0.f, joyY = 0.f;

    cdrom_cdda_play(1, 1, 15, CDDA_TRACKS);

    while (!WindowShouldClose())
    {
        //fpsCam.UpdateCamera(GetFrameTime());
        SceneManager::GetInstance().Update();

        joyX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        joyY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            SceneManager::GetInstance().Draw3D();
            SceneManager::GetInstance().Draw();
            
            DrawText(TextFormat("Analog stick: X=%.2f, Y=%0.2f", joyX, joyY), 10, 310, 20, BLACK);
            DrawFPS(10, 10);

        EndDrawing();
    }
    cdrom_cdda_pause();

    CloseWindow();
    return 0;
}