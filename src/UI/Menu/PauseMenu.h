#pragma once
#include <Gameplay/Inventory/InventoryManager.h>
#include <vector>

class Canvas;

class PauseMenu
{
public:
    PauseMenu();
    ~PauseMenu();

public:
    void OnDraw2D();
    void OnUpdate();

    void DisableCanvasHack();
private:
    void LoadInventoryItems();
private:
    std::vector<InventoryItem*> m_InventoryItems;
    Canvas* m_Canvas;
    bool m_IsActive = false;
};