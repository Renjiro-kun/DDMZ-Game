#pragma once
#include <raylib/raylib.h>


class UIRepository
{
public:
    static UIRepository& GetInstance()
    {
        static UIRepository instance;
        return instance;
    }
public:
    void Init();

    void Shutdown();

    Font& GetButtonFont() { return m_ButtonsFont; }

private:
    Font m_ButtonsFont;
};