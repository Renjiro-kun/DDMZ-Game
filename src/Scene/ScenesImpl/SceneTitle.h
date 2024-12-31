#pragma once
#include <Scene/Scene.h>
#include <raylib/raylib.h>
#include <vector>
#include <UI/Canvas.h>

class SceneTitle : public Scene
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
    Font m_AdvFont;
    Texture2D* m_AdvTextures;
    Texture2D m_EarthTexture;
    Rectangle m_EarthSourceRect;
    Rectangle m_EarthDestRect;

    const int8_t widthCount = 3;
    const int8_t heightCount = 2;
    const float m_RotationSpeed{2.f};
    float m_Rotation{0.f};

    Camera m_Camera;
};