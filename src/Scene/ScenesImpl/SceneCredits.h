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
    const std::array<std::string, 11> m_CreditsString
    {
        "GAME MADE WITH ",
        "raylib\n&\nKalistiOS",
        "FONTS USED",
        "Pica Hole by Apostrophic Labs\nShmup In The Zone by Goma Shin\nMona Sans by Degarism",
        "SFX USED",
        "freesoundlibrary.org\nGuyEngine VST by SoundFontGuy",
        "TEXTURES USED",
        "\"The Blue Marble\" \nfrom NASA Johnson Space Center",
        "GAME CREATED BY",
        "Renji-kun",
        "THANKS FOR PLAYING THE GAME"
    };
    Camera m_Camera;
    float m_Alpha;

    char m_CurrentText = 0;
    char m_State = 0;    
};