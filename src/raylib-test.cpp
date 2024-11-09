#include <kos.h>

#include "test.h"
#include "FirstPersonCamera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>

#include <raylib/raylib.h>

bool flag = true;
bool xFlag = false;
maple_device_t* cont;
cont_state_t *padState;

void UpdateController()
{
    cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

    if(!padState)
    {
        printf("Error reading controller");
    }

    if(padState->buttons & CONT_START)
    {
        flag = 0;
    }

    if(padState->buttons & CONT_A)
    {
        xFlag = !xFlag;
    }
}

int main()
{
    const int SCREEN_WIDTH = WIDTH;
    const int SCREEN_HEIGHT = HEIGHT;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test window");
    SetTargetFPS(TARGET_FPS);

    // Camera init
    FirstPersonCamera fpsCam;

    Image img = LoadImage("/rd/cubicmap.png");
    Texture2D cubicmap = LoadTextureFromImage(img);

    Mesh mesh = GenMeshCubicmap(img, Vector3{1.f, 1.f, 1.f});
    Model model = LoadModelFromMesh(mesh);

    Texture2D texture = LoadTexture("/rd/cubicmap_atlas.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    Color* mapPixels = LoadImageColors(img);

    Vector3 mapPosition = { -16.0f, 0.0f, -8.0f };          // Set model position
    UnloadImage(img);

    while (flag)
    {
        UpdateController();
        fpsCam.UpdateCamera(GetFrameTime());

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            BeginMode3D(fpsCam.GetCamera());
                DrawModel(model, mapPosition, 1.f, WHITE);
            EndMode3D();
            
            DrawTextureEx(cubicmap, Vector2{640 - cubicmap.width*4.f - 20.f, 20.f}, 0.f,1.f, WHITE);

            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadImageColors(mapPixels);

    UnloadTexture(cubicmap);
    UnloadTexture(texture);
    UnloadModel(model);

    CloseWindow();
    return 0;
}