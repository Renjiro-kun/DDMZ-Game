#pragma once
#include <UI/Widget.h>
#include <string>

class Toggle : public Widget
{
public:
    Toggle();
    Toggle(Vector2 position, const std::string& buttonText, void (*pressedCallback)(Toggle* sender) = nullptr, void(*focusedCallback)(Toggle* sender) = nullptr, void(*setValueCallback)(bool value) = nullptr, bool (*getValueCallback)() = nullptr);
    ~Toggle();

    void OnDraw2D() override;
    void SetFocused(bool focused) override;
    void OnPressed() override;

    void OnScaleUp() {}
    void OnScaleDown() {}

    void SetPosition(Vector2 position) { m_Position = position; }

private:
    void InitData();
    void SetCurrentState(char state);
    
    const std::string& GetValueText(bool value);
    
private:
    void (*onTogglePressedCallback)(Toggle* sender);
    void (*onToggleFocusedCallback)(Toggle* sender);
    bool (*getToggleValue)();
    void (*setToggleValue)(bool value);
private:
    const std::string m_OnText = "ON";
    const std::string m_OffText = "OFF";
    Vector2 m_Position;
    char m_CurrentState;

    std::string m_ButtonText;
    std::string m_TextToRender;
    bool m_Value;
};