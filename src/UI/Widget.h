#pragma once
#include <raylib/raylib.h>

class Widget
{
public:
    virtual void OnDraw2D() = 0;
    virtual void SetFocused(bool focused) = 0;
    virtual void OnPressed() = 0;
    virtual void SetPosition(Vector2 position) = 0;
};