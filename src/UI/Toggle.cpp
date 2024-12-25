#include <UI/Toggle.h>
#include <UI/UIRepository.h>
#include <Sound/SfxManager.h>

Toggle::Toggle()
{
    InitData();
}

Toggle::~Toggle()
{
    m_ButtonText.clear();
    m_TextToRender.clear();
}

Toggle::Toggle(Vector2 position, const std::string& buttonText, void (*pressedCallback)(Toggle* sender), void(*focusedCallback)(Toggle* sender), void(*setValueCallback)(bool value), bool (*getValueCallback)())
{
    m_Position = position;
    m_ButtonText = buttonText;
    onTogglePressedCallback = pressedCallback;
    onToggleFocusedCallback = focusedCallback;
    setToggleValue = setValueCallback;
    getToggleValue = getValueCallback;
    InitData();
}

void Toggle::InitData()
{
    m_CurrentState = 0;
    m_Value = getToggleValue();
    m_TextToRender = TextFormat(" %s: %s", m_ButtonText.c_str(), GetValueText(getToggleValue()).c_str());
}

const std::string& Toggle::GetValueText(bool value)
{
    return value ? m_OnText : m_OffText;
}

void Toggle::OnDraw2D()
{
    DrawTextEx(UIRepository::GetInstance().GetButtonFont(), m_TextToRender.c_str(), m_Position, UIRepository::GetInstance().GetButtonFont().baseSize, 1, WHITE);
}

void Toggle::OnPressed()
{
    SetCurrentState(2);
    m_Value = !m_Value;
    setToggleValue(m_Value);
    m_Value = getToggleValue();
    m_TextToRender = TextFormat(">%s: %s<", m_ButtonText.c_str(), GetValueText(getToggleValue()).c_str());
    SFXManager::GetInstance().Play(UIRepository::GetInstance().GetClickSFX());
    if(onTogglePressedCallback != nullptr)
    {
        onTogglePressedCallback(this);
    }
}

void Toggle::SetFocused(bool focus)
{
    focus ? SetCurrentState(1) : SetCurrentState(0);
    std::string baseText = TextFormat("%s: %s", m_ButtonText.c_str(), GetValueText(getToggleValue()).c_str());
    focus ? m_TextToRender = TextFormat(">%s<", baseText.c_str()) : m_TextToRender = TextFormat(" %s ", baseText.c_str());
    if(focus)
    {
        SFXManager::GetInstance().Play(UIRepository::GetInstance().GetFocusSFX());
    }
    if(onToggleFocusedCallback != nullptr)
    {
        onToggleFocusedCallback(this);
    }
}

void Toggle::SetCurrentState(char state)
{
    m_CurrentState = state;
}