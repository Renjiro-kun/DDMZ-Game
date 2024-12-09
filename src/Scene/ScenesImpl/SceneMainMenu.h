#pragma once
#include <Scene/Scene.h>
#include <raylib/raylib.h>
#include <vector>
#include <UI/Canvas.h>

class SceneMainMenu : public Scene
{
public:
    void OnActivated() override;
    void OnDectivated() override;
    void OnUpdate() override;
    void OnDraw3D() override;
    void OnDraw2D() override;
    Camera& GetCamera() override { return m_Camera; }
    Color GetSceneBackgroundColor() override { return BLACK; }
private:
    //Font m_AdvFont;
    Texture2D* m_AdvTextures;

    Canvas* m_MenuCanvas = nullptr;

    const int8_t widthCount = 3;
    const int8_t heightCount = 2;

    Camera m_Camera;
};