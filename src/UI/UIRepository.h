#pragma once
#include <raylib/raylib.h>
#include <Sound/SfxManager.h>

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

    SFXHandle GetFocusSFX() { return m_FocusSFX; }
    SFXHandle GetClickSFX() { return m_ClickSFX; }
    SFXHandle GetScaleSFX() { return m_ScaleSFX; }
    SFXHandle GetBadSFX() { return m_BadSFX; }

private:
    Font m_ButtonsFont;
    SFXHandle m_FocusSFX;
    SFXHandle m_ClickSFX;
    SFXHandle m_ScaleSFX;
    SFXHandle m_BadSFX;
};