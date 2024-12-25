#include <Defines.h>
#include <UI/UIRepository.h>

void UIRepository::Init()
{
    m_ButtonsFont = LoadFont(GET_ASSET_FROM_RD("font_ui_button.png")); 
    m_ClickSFX = SFXManager::GetInstance().LoadSFX(GET_ASSET_FROM_RD("sfx_ui_click.wav"));
    m_FocusSFX = SFXManager::GetInstance().LoadSFX(GET_ASSET_FROM_RD("sfx_ui_focus.wav"));
    m_ScaleSFX = SFXManager::GetInstance().LoadSFX(GET_ASSET_FROM_RD("sfx_ui_slider.wav"));
    m_BadSFX = SFXManager::GetInstance().LoadSFX(GET_ASSET_FROM_RD("sfx_ui_unavailable.wav"));
}

void UIRepository::Shutdown()
{
    SFXManager::GetInstance().Unload(m_BadSFX);
    SFXManager::GetInstance().Unload(m_FocusSFX);
    SFXManager::GetInstance().Unload(m_ScaleSFX);
    SFXManager::GetInstance().Unload(m_ClickSFX);
    UnloadFont(m_ButtonsFont);
}