#pragma once
#include <Scene/Scene.h>

#include <string>
#include <array>

class SceneCredits : public Scene
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
    const std::array<std::string, 2> m_CreditsString
    {
        "Directed by: \n Test Test",
        "Game by: \n Test Test"
    };
    Camera m_Camera;
    float m_Alpha;

    char m_CurrentText = 0;
    char m_State = 0;    
};