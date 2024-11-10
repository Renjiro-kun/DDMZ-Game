#pragma once
#include "Scene.h"
#include <raylib/raylib.h>

class SceneMainMenu : public Scene
{
public:
    void OnActivated() override;
    void OnDectivated() override;
    void OnUpdate() override;
    void OnDraw3D() override;
    void OnDraw2D() override;
    Camera& GetCamera() override { return m_Camera; }

private:
    Camera m_Camera;
};