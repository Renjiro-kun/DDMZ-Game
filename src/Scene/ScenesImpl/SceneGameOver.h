#pragma once
#include <Scene/Scene.h>

class SceneGameOver : public Scene
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
    void ExitScene();
private:
    Camera m_Camera;
    int m_FramesCounter;
    float m_Alpha;

    char m_State = 0;    
};