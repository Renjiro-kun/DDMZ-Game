#pragma once
#include <vector>


class Widget;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    void OnDraw2D();
    void OnUpdate();

    void AddWidget(Widget* widget);

private:
    void UpdateFocusedStates();
private:
    std::vector<Widget*> m_WidgetsContainer;
    int m_CurrentFocusIdx = 0;
    int m_LastFocusIdx = 0;
};