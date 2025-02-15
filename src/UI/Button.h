#pragma once
#include <UI/Widget.h>
#include <string>

class Button : public Widget
{
public:
    Button();
    Button(Vector2 position, const std::string& buttonText, void (*pressedCallback)() = nullptr, void(*focusedCallback)() = nullptr);
    ~Button();

    void OnDraw2D() override;
    void SetFocused(bool focused) override;
    void OnPressed() override;

    void OnScaleUp() {}
    void OnScaleDown() {}

    void SetPosition(Vector2 position) { m_Position = position; }

private:
    void InitData();

    void SetCurrentState(char state);
private:
    void (*onButtonPressedCallback)();
    void (*onButtonFocusedCallback)();
private:
    Vector2 m_Position;
    char m_CurrentState;

    std::string m_ButtonText;
    std::string m_TextToRender;
};