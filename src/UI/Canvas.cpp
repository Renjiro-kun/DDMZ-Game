#include <UI/Canvas.h>
#include <UI/Widget.cpp>

#include <raylib/raylib.h>

Canvas::Canvas()
{
    m_CurrentFocusIdx = 0;
    m_LastFocusIdx = 0;
}

Canvas::~Canvas()
{
    for (size_t i = 0; i < m_WidgetsContainer.size(); i++)
    {
        delete m_WidgetsContainer[i];
    }
}

void Canvas::AddWidget(Widget* widget)
{
    m_WidgetsContainer.emplace_back(widget);
    UpdateFocusedStates();
}

void Canvas::OnUpdate()
{
    m_LastFocusIdx = m_CurrentFocusIdx;
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
        {
            m_CurrentFocusIdx++;
            if(m_CurrentFocusIdx >= m_WidgetsContainer.size()) m_CurrentFocusIdx = m_WidgetsContainer.size() - 1;
        }
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP))
        {
            m_CurrentFocusIdx--;
            if(m_CurrentFocusIdx < 0) m_CurrentFocusIdx = 0;
        }
        if(m_LastFocusIdx != m_CurrentFocusIdx)
        {
            UpdateFocusedStates();
        }
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
        {
            m_WidgetsContainer[m_CurrentFocusIdx]->OnPressed();
        }
    }
}

void Canvas::OnDraw2D()
{
    for (size_t i = 0; i < m_WidgetsContainer.size(); i++)
    {
        m_WidgetsContainer[i]->OnDraw2D();
    }   
}

void Canvas::UpdateFocusedStates()
{
    for (size_t i = 0; i < m_WidgetsContainer.size(); i++)
    {
        m_WidgetsContainer[i]->SetFocused(false);
        if(i == m_CurrentFocusIdx)
        {
            m_WidgetsContainer[i]->SetFocused(true);
        }
    }
}