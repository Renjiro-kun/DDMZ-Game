#pragma once

class Canvas;

class PauseMenu
{
public:
    PauseMenu();
    ~PauseMenu();

public:
    void OnDraw2D();
    void OnUpdate();

    void DisableCanvasHack();

private:
    Canvas* m_Canvas;
    bool m_IsActive = false;
};