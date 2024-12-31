#pragma once

class TimerController
{
public:
    static TimerController& GetInstance()
    {
        static TimerController instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void Update();
    void OnDraw2D();

    void StartTimer(float duration);
    void StopTimer();

    void PauseTimer();
    void UnpauseTimer();
    float GetCurrentTime() { return m_CurrentTime; }

    bool IsElapsed() { return m_IsElapsed; }
private:
    TimerController() = default;
    ~TimerController() = default;
    TimerController(const TimerController&) = delete;
    TimerController& operator=(const TimerController&) = delete;

private:
    float m_CurrentTime{0.f};

    bool m_Started{false};
    bool m_IsElapsed{true};
};