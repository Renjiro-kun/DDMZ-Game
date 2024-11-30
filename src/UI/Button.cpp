#include <UI/Button.h>

Button::Button()
{
    m_ButtonTexture = LoadTexture("/rd/btn_test.png");

    m_FrameHeight = (float)m_ButtonTexture.height / 3;
    m_CurrentStateRect = { 0, 0, (float)m_ButtonTexture.width, m_FrameHeight };
    m_CurrentState = 0;
}

Button::~Button()
{
    UnloadTexture(m_ButtonTexture);
}

Button::Button(Vector2 position, void (*pressedCallback)(), void(*focusedCallback)())
{
    m_Position = position;
    InitData();
    onButtonPressedCallback = pressedCallback;
    onButtonFocusedCallback = focusedCallback;
}

void Button::InitData()
{
    m_ButtonTexture = LoadTexture("/rd/btn_test.png");
    m_FrameHeight = (float)m_ButtonTexture.height / 3;
    m_CurrentStateRect = { 0, 0, (float)m_ButtonTexture.width, m_FrameHeight };
    m_CurrentState = 0;
}

void Button::OnDraw2D()
{
    DrawTextureRec(m_ButtonTexture, m_CurrentStateRect, m_Position, WHITE);
}

void Button::OnPressed()
{
    SetCurrentState(2);
    if(onButtonPressedCallback != nullptr)
    {
        onButtonPressedCallback();
    }
}

void Button::SetFocused(bool focus)
{
    focus ? SetCurrentState(1) : SetCurrentState(0);
    if(onButtonFocusedCallback != nullptr)
    {
        onButtonFocusedCallback();
    }
}

void Button::SetCurrentState(char state)
{
    m_CurrentState = state;
    m_CurrentStateRect.y = m_FrameHeight * m_CurrentState;
}