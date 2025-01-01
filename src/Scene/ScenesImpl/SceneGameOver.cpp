#include <Defines.h>
#include <Scene/ScenesImpl/SceneGameOver.h>
#include <Scene/SceneManager.h>

#include <UI/UIRepository.h>

void SceneGameOver::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_FramesCounter = 0;
    m_Alpha = 0.f;
}

void SceneGameOver::OnDectivated()
{

}

void SceneGameOver::OnDraw3D()
{

}

void SceneGameOver::OnDraw2D()
{
    DrawTextEx(UIRepository::GetInstance().GetButtonFont(), "GAME OVER", Vector2{150, HEIGHT / 2}, 32, 1, Fade(WHITE, m_Alpha)); 
}

void SceneGameOver::OnUpdate()
{
    if(m_State == 0)
    {
        m_Alpha += 0.01f;
        if(m_Alpha >= 1.f)
        {
            m_Alpha = 1.f;
            m_State = 1;
        }
    }
    else if(m_State == 1)
    {
        m_Alpha -= 0.01f;
        if(m_Alpha <= 0.f)
        {
            m_Alpha = 0.f;
            m_State = 2;
        }
    }
    else if(m_State == 2)
    {
        SceneManager::GetInstance().LoadScene(SceneId::SCENE_TITLE_SCREEN);
    }
}