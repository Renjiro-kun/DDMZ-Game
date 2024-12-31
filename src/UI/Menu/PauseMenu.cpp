#include <Defines.h>
#include <UI/Menu/PauseMenu.h>

#include <Gameplay/TimerController.h>
#include <Scene/SceneManager.h>
#include <UI/UIRepository.h>
#include <UI/Canvas.h>
#include <UI/Button.h>

void OnExitPressed();

PauseMenu::PauseMenu()
{
    m_Canvas = new Canvas(InputContext::PauseMenu);
    m_Canvas->AddWidget(new Button(Vector2{WIDTH - 150, HEIGHT - 100}, "EXIT", OnExitPressed));
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
            if(m_IsActive)
            {
                LoadInventoryItems();
                TimerController::GetInstance().PauseTimer();
            }
            else
            {
                m_InventoryItems.clear();
                TimerController::GetInstance().UnpauseTimer();
            }
            m_Canvas->SetActive(m_IsActive);
        }
    }

    m_Canvas->OnUpdate();
}

void PauseMenu::OnDraw2D()
{
    if(m_IsActive)
    {   
        DrawTextEx(UIRepository::GetInstance().GetButtonFont(), "ITEMS: ", Vector2{150, 50}, 28, 1, WHITE);
        for (size_t i = 0; i < m_InventoryItems.size(); i++)
        {
            DrawTextEx(UIRepository::GetInstance().GetButtonFont(), m_InventoryItems[i]->name.c_str(), Vector2{200, (float)100+(i*25)}, 20, 1, WHITE);
        }
    }
    
    m_Canvas->OnDraw2D();
}

void PauseMenu::DisableCanvasHack()
{
    m_Canvas->SetActive(false);
}

void PauseMenu::LoadInventoryItems()
{
    auto& invIds = InventoryManager::GetInstance().GetPlayerItems();
    for (size_t i = 0; i < invIds.size(); i++)
    {
        m_InventoryItems.push_back(&InventoryManager::GetInstance().GetItemInfo(invIds[i]));
    }
}

void OnExitPressed()
{
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_TITLE_SCREEN);
}