#include <Defines.h>
#include <UI/Menu/PauseMenu.h>

#include <Scene/SceneManager.h>
#include <UI/Canvas.h>
#include <UI/Button.h>

void OnExitPressed();

PauseMenu::PauseMenu()
{
    m_Canvas = new Canvas(InputContext::PauseMenu);
    m_Canvas->AddWidget(new Button(Vector2{200, 200}, "EXIT", OnExitPressed));
}

PauseMenu::~PauseMenu()
{
    delete m_Canvas;
}

void PauseMenu::OnUpdate()
{
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT))
        {
            m_IsActive = !m_IsActive;
            m_Canvas->SetActive(m_IsActive);
        }
    }

    m_Canvas->OnUpdate();
}

void PauseMenu::OnDraw2D()
{
    m_Canvas->OnDraw2D();
}

void PauseMenu::DisableCanvasHack()
{
    m_Canvas->SetActive(false);
}

void OnExitPressed()
{
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_TITLE_SCREEN);
}