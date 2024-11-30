#pragma once
#include <UI/Widget.h>

class Button : public Widget
{
public:
    Button();
    Button(Vector2 position, void (*pressedCallback)() = nullptr, void(*focusedCallback)() = nullptr);
    ~Button();

    void OnDraw2D() override;
    void SetFocused(bool focused) override;
    void OnPressed() override;

    void SetPosition(Vector2 position) { m_Position = position; }

private:
    void InitData();

    void SetCurrentState(char state);
private:
    void (*onButtonPressedCallback)();
    void (*onButtonFocusedCallback)();
private:
    Texture2D m_ButtonTexture;
    Rectangle m_CurrentStateRect;
    Vector2 m_Position;
    char m_CurrentState;
    float m_FrameHeight;
};