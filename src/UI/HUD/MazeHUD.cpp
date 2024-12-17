#include <Defines.h>
#include <UI/HUD/MazeHUD.h>


void MazeHUD::OnActivate()
{
    m_HUDTexture = LoadTexture("/rd/HUD_MZ_Test.png");
}

void MazeHUD::OnDeactivate()
{
    UnloadTexture(m_HUDTexture);
}

void MazeHUD::OnDraw2D()
{
    if(m_IsInteractActive)
    {
        DrawTextureRec(m_HUDTexture, InteractRect, Vector2{WIDTH / 2 - 100, HEIGHT - 100}, WHITE);
    }
}