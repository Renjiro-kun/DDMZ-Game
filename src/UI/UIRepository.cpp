#include <UI/UIRepository.h>

void UIRepository::Init()
{
    m_ButtonsFont = LoadFont("/rd/font_ui_button.png");
}

void UIRepository::Shutdown()
{
    UnloadFont(m_ButtonsFont);
}