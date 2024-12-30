#include <Defines.h>
#include <Scene/ScenesImpl/SceneIntro.h>
#include <Scene/SceneManager.h>

void SceneIntro::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_LogoPositionX = WIDTH / 2 - 128;
    m_LogoPositionY = HEIGHT / 2 -128;

    m_FramesCounter = 0;
    m_LettersCount = 0;
    m_Alpha = 1.f;
    m_KOSLogo = LoadTexture(GET_ASSET_FROM_RD("KOS_Logo.png"));

    m_TopSideRecWidth = 16;
    m_LeftSideRecHeight = 16;
    m_BottomSideRecWidth = 16;
    m_RightSideRecHeight = 16;
}

void SceneIntro::OnDectivated()
{
    UnloadTexture(m_KOSLogo);   
}

void SceneIntro::OnDraw3D()
{

}

void SceneIntro::OnDraw2D()
{
    if(m_State == 0)
    {
        if((m_FramesCounter/15)%2) DrawRectangle(m_LogoPositionX, m_LogoPositionY, 16, 16, BLACK);
    }
    else if (m_State == 1)
    {
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, m_TopSideRecWidth, 16, BLACK);
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, 16, m_LeftSideRecHeight, BLACK);
    }
    else if (m_State == 2)
    {
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, m_TopSideRecWidth, 16, BLACK);
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, 16, m_LeftSideRecHeight, BLACK);

        DrawRectangle(m_LogoPositionX + 240, m_LogoPositionY, 16, m_RightSideRecHeight, BLACK);
        DrawRectangle(m_LogoPositionX, m_LogoPositionY + 240, m_BottomSideRecWidth, 16, BLACK);
    }
    else if (m_State == 3)
    {
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, m_TopSideRecWidth, 16, Fade(BLACK, m_Alpha));
        DrawRectangle(m_LogoPositionX, m_LogoPositionY, 16, m_LeftSideRecHeight, Fade(BLACK, m_Alpha));

        DrawRectangle(m_LogoPositionX + 240, m_LogoPositionY, 16, m_RightSideRecHeight, Fade(BLACK, m_Alpha));
        DrawRectangle(m_LogoPositionX, m_LogoPositionY + 240, m_BottomSideRecWidth, 16, Fade(BLACK, m_Alpha)); 

        DrawRectangle(WIDTH/2-112, HEIGHT/2-112, 224, 224, Fade(RAYWHITE, m_Alpha));

        DrawText(TextSubtext("raylib", 0, m_LettersCount), WIDTH/2-44, HEIGHT/2+48, 50, Fade(BLACK, m_Alpha));
    }
    else if (m_State == 4 || m_State == 5)
    {
        DrawTexture(m_KOSLogo, 50, 0, Fade(WHITE, m_Alpha));
    }
}

void SceneIntro::OnUpdate()
{
    if(m_State == 0)
    {
        m_FramesCounter++;

        if(m_FramesCounter == 120)
        {
            m_State = 1;
            m_FramesCounter = 0;
        }
    }
    else if (m_State == 1)
    {
        m_TopSideRecWidth += 4;
        m_LeftSideRecHeight += 4;
        if(m_TopSideRecWidth == 256) m_State = 2;   
    }
    else if (m_State == 2)
    {
        m_BottomSideRecWidth += 4;
        m_RightSideRecHeight += 4;
        if(m_BottomSideRecWidth == 256) m_State = 3;
    }
    else if (m_State == 3)
    {
        m_FramesCounter++;

        if(m_FramesCounter / 12)
        {   
            m_LettersCount++;
            m_FramesCounter = 0;
        }

        if(m_LettersCount >= 10)
        {
            m_Alpha -= 0.02f;

            if(m_Alpha <= 0.f)
            {
                m_Alpha = 0.f;
                m_State = 4;
            }
        }
    }
    else if (m_State == 4)
    {
        m_Alpha += 0.009f;

        if(m_Alpha >= 1.f)
        {
            m_Alpha = 1.f;
            m_State = 5;
        }
    }
    else if(m_State == 5)
    {
        m_Alpha -= 0.009f;

        if(m_Alpha <= 0.f)
        {
            m_Alpha = 0.f;
            m_State = 6;
        }
    }
    else if(m_State == 6)
    {
        SceneManager::GetInstance().LoadScene(SceneId::SCENE_TITLE_SCREEN);
    }
    
    
    
    

    // if(IsGamepadAvailable(0))
    // {
    //     if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    //     {   
    //         SceneManager::GetInstance().LoadScene(SceneId::SCENE_TITLE_SCREEN);
    //     }
    // }
}