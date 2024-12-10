#pragma once
#include <vector>
#include <Input/InputContextManager.h>

class Widget;

class Canvas
{
public:
    Canvas(InputContext context);
    ~Canvas();

    void OnDraw2D();
    void OnUpdate();

    void AddWidget(Widget* widget);

    void SetActive(bool active) { m_Active = active; ManageInputContext(); }
private:
    void UpdateFocusedStates();
    void ManageInputContext();
private:
    std::vector<Widget*> m_WidgetsContainer;
    int m_CurrentFocusIdx = 0;
    int m_LastFocusIdx = 0;
    bool m_Active = false;
    InputContext m_CanvasContext = InputContext::Invalid;
};