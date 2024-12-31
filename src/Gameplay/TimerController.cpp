#include <Defines.h>
#include <Gameplay/TimerController.h>
#include <UI/UIRepository.h>

#include <raylib/raylib.h>

void TimerController::Init()
{

}

void TimerController::Shutdown()
{

}

void TimerController::Update()
{
    if(m_Started && !m_IsElapsed)
    {
        m_CurrentTime -= GetFrameTime();
        if(m_CurrentTime <= 0)
        {
            m_IsElapsed = true;
        }
    }
}

void TimerController::OnDraw2D()
{
    if(m_Started)
    {
        float minutes = floor(m_CurrentTime / 60.f);
        DrawTextEx(UIRepository::GetInstance().GetButtonFont(), 
                    TextFormat("%01.00f:%02.00f", minutes, m_CurrentTime - (minutes * 60.f)),
                    Vector2{ WIDTH/2 - 120, 20 }, 30, 1, RED);
    }
}

void TimerController::StartTimer(float duration)
{
    m_Started = true;
    m_IsElapsed = false;
    m_CurrentTime = duration;
}

void TimerController::PauseTimer()
{
    m_Started = false;
}

void TimerController::UnpauseTimer()
{
    m_Started = true;
}

void TimerController::StopTimer()
{
    m_Started = false;
    m_IsElapsed = true;
    m_CurrentTime = 0.f;
}