#include <UI/Canvas.h>
#include <UI/Widget.cpp>

#include <raylib/raylib.h>

Canvas::Canvas(InputContext context)
{
    m_CurrentFocusIdx = 0;
    m_LastFocusIdx = -1;
    m_CanvasContext = context;
}

Canvas::~Canvas()
{
    if(m_Active)
    {
        SetActive(false);
    }
    
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
    if( m_Active &&
        IsGamepadAvailable(0) &&
        InputContextManager::GetInstance().CurrentInputComtext() == m_CanvasContext )
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
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
        {
            m_WidgetsContainer[m_CurrentFocusIdx]->OnScaleDown();
        }
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
        {
            m_WidgetsContainer[m_CurrentFocusIdx]->OnScaleUp();
        }
    }
}

void Canvas::OnDraw2D()
{
    if(m_Active)
    {
        for (size_t i = 0; i < m_WidgetsContainer.size(); i++)
        {
            m_WidgetsContainer[i]->OnDraw2D();
        }   
    }
}

void Canvas::ManageInputContext()
{
    m_Active ? InputContextManager::GetInstance().SetInputContext(m_CanvasContext) : InputContextManager::GetInstance().RestoreContext();
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