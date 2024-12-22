#include <Defines.h>
#include <UI/UIRepository.h>

void UIRepository::Init()
{
    m_ButtonsFont = LoadFont(GET_ASSET_FROM_RD("font_ui_button.png")); 
}

void UIRepository::Shutdown()
{
    UnloadFont(m_ButtonsFont);
}