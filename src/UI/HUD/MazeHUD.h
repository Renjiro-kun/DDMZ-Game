#pragma once
#include <raylib/raylib.h>

class MazeHUD
{
public:
    void OnActivate();
    void OnDeactivate();

    void OnDraw2D();

    void SetInteractActive(bool value) {m_IsInteractActive = value;}

private:
    const Rectangle InteractRect{0, 0, 256, 128};

    Texture2D m_HUDTexture;

    bool m_IsInteractActive;
};