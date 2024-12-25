#include <UI/Button.h>
#include <UI/UIRepository.h>
#include <Sound/SfxManager.h>

Button::Button()
{
    InitData();
}

Button::~Button()
{
    m_ButtonText.clear();
    m_TextToRender.clear();
}

Button::Button(Vector2 position, const std::string& buttonText, void (*pressedCallback)(), void(*focusedCallback)())
{
    m_Position = position;
    m_ButtonText = buttonText;
    InitData();
    onButtonPressedCallback = pressedCallback;
    onButtonFocusedCallback = focusedCallback;
}

void Button::InitData()
{
    m_CurrentState = 0;
    m_TextToRender = TextFormat(" %s ", m_ButtonText.c_str());
}

void Button::OnDraw2D()
{
    DrawTextEx(UIRepository::GetInstance().GetButtonFont(), m_TextToRender.c_str(), m_Position, UIRepository::GetInstance().GetButtonFont().baseSize, 1, WHITE);
}

void Button::OnPressed()
{
    SetCurrentState(2);
    SFXManager::GetInstance().Play(UIRepository::GetInstance().GetClickSFX());
    if(onButtonPressedCallback != nullptr)
    {
        onButtonPressedCallback();
    }
}

void Button::SetFocused(bool focus)
{
    focus ? SetCurrentState(1) : SetCurrentState(0);
    focus ? m_TextToRender = TextFormat(">%s<", m_ButtonText.c_str()) : m_TextToRender = TextFormat(" %s ", m_ButtonText.c_str());
    if(focus)
    {
        SFXManager::GetInstance().Play(UIRepository::GetInstance().GetFocusSFX());
    }
    if(onButtonFocusedCallback != nullptr)
    {
        onButtonFocusedCallback();
    }
}

void Button::SetCurrentState(char state)
{
    m_CurrentState = state;
}