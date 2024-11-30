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

Button::Button(Vector2 position)
{
    m_Position = position;

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
}

void Button::SetFocused(bool focus)
{
    focus ? SetCurrentState(1) : SetCurrentState(0);
}

void Button::SetCurrentState(char state)
{
    m_CurrentState = state;
    m_CurrentStateRect.y = m_FrameHeight * m_CurrentState;
}