#pragma once
#include <raylib/raylib.h>

class Scene
{
public:
    virtual void OnActivated() = 0;
    virtual void OnDectivated() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnDraw3D() = 0;
    virtual void OnDraw2D() = 0;
    virtual Camera& GetCamera() = 0;

    virtual Color GetSceneBackgroundColor() { return RAYWHITE; }
};