#pragma once
#include <Scene/Scene.h>

class SceneIntro : public Scene
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
    int m_FramesCounter;
    int m_LogoPositionX;
    int m_LogoPositionY;
    float m_Alpha;

    short m_TopSideRecWidth;
    short m_LeftSideRecHeight;
    short m_BottomSideRecWidth;
    short m_RightSideRecHeight;

    short m_LettersCount;
    char m_State = 0;
    
};