#include <UI/Slider.h>
#include <UI/UIRepository.h>
#include <Sound/SfxManager.h>

Slider::Slider()
{
    InitData();
}

Slider::~Slider()
{
    m_ButtonText.clear();
    m_TextToRender.clear();
}

Slider::Slider(Vector2 position, const std::string& buttonText, int step, int minValue, int maxValue,
    void (*setValue)(int), int (*getValue)(),
    void (*pressedCallback)(), void(*focusedCallback)(), void(*upCallback)(), void(*downCallvack)())
{
    m_Position = position;
    m_ButtonText = buttonText;
    m_MinValue = minValue;
    m_MaxValue = maxValue;
    m_Step = step;
    onSliderPressedCallback = pressedCallback;
    onSliderFocusedCallback = focusedCallback;
    onSliderUpCallback = upCallback;
    onSliderDownCallback = downCallvack;
    setSliderValue = setValue;
    getSliderValue = getValue;
    InitData();
}

void Slider::InitData()
{
    m_CurrentState = 0;
    m_Value = getSliderValue();
    m_TextToRender = TextFormat(" %s: %d ", m_ButtonText.c_str(), m_Value);
}

void Slider::OnDraw2D()
{
    DrawTextEx(UIRepository::GetInstance().GetButtonFont(), m_TextToRender.c_str(), m_Position, UIRepository::GetInstance().GetButtonFont().baseSize, 1, WHITE);
}

void Slider::OnPressed()
{
    SetCurrentState(2);
    if(onSliderPressedCallback != nullptr)
    {
        onSliderPressedCallback();
    }
}

void Slider::SetFocused(bool focus)
{
    focus ? SetCurrentState(1) : SetCurrentState(0);
    std::string baseText = TextFormat("%s: %d", m_ButtonText.c_str(), m_Value);
    focus ? m_TextToRender = TextFormat(">%s<", baseText.c_str()) : m_TextToRender = TextFormat(" %s ", baseText.c_str());
    if(focus)
    {
        SFXManager::GetInstance().Play(UIRepository::GetInstance().GetFocusSFX());
    }
    if(onSliderFocusedCallback != nullptr)
    {
        onSliderFocusedCallback();
    }
}

void Slider::OnScaleDown()
{
    m_Value -= m_Step;
    if(m_Value < m_MinValue)
    {
        m_Value = m_MinValue;
    }
    setSliderValue(m_Value);
    
    m_TextToRender = TextFormat(">%s: %d<", m_ButtonText.c_str(), m_Value);
    SFXManager::GetInstance().Play(UIRepository::GetInstance().GetScaleSFX());
    
    if(onSliderDownCallback)
    {
        onSliderDownCallback();
    }
}

void Slider::OnScaleUp()
{
    m_Value += m_Step;
    if(m_Value > m_MaxValue)
    {
        m_Value = m_MaxValue;
    }
    setSliderValue(m_Value);
    m_TextToRender = TextFormat(">%s: %d<", m_ButtonText.c_str(), m_Value);
    SFXManager::GetInstance().Play(UIRepository::GetInstance().GetScaleSFX());

    if(onSliderUpCallback)
    {
        onSliderUpCallback();
    }
}

void Slider::SetCurrentState(char state)
{
    m_CurrentState = state;
}