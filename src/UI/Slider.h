#pragma once
#include <UI/Widget.h>
#include <string>

class Slider : public Widget
{
public:
    Slider();
    Slider(Vector2 position, const std::string& buttonText, int step, int minValue, int maxValue,
            void (*setValue)(int), int (*getValue)(),
            void (*pressedCallback)() = nullptr, void(*focusedCallback)() = nullptr, void(*upCallback)() = nullptr, void(*downCallvack)() = nullptr
            );
    ~Slider();

    void OnDraw2D() override;
    void SetFocused(bool focused) override;
    void OnPressed() override;

    void OnScaleUp() override;
    void OnScaleDown() override;

    void SetPosition(Vector2 position) { m_Position = position; }

private:
    void InitData();

    void SetCurrentState(char state);
private:
    void (*onSliderPressedCallback)();
    void (*onSliderFocusedCallback)();
    void (*onSliderUpCallback)();
    void (*onSliderDownCallback)();
    int (*getSliderValue)();
    void (*setSliderValue)(int);
private:
    Vector2 m_Position;
    char m_CurrentState;

    std::string m_ButtonText;
    std::string m_TextToRender;

    int m_MaxValue;
    int m_MinValue;
    int m_Step;

    int m_Value{0};
};