#include <Defines.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <VMU/SaveManager.h>

#include <algorithm>

void InventoryManager::Init()
{

}

void InventoryManager::Shutdown()
{
    m_PlayerItems.clear();
}

bool InventoryManager::HasItem(size_t id)
{
    auto item = std::find_if(m_PlayerItems.begin(), m_PlayerItems.end(), [&id](size_t itemId){
        return itemId == id;
    });
    
    return item != m_PlayerItems.end();
}

void InventoryManager::UseItem(size_t id)
{
    auto item = std::find_if(m_PlayerItems.begin(), m_PlayerItems.end(), [&id](size_t itemId){
        return itemId == id;
    });

    if(item != m_PlayerItems.end())
    {
        m_PlayerItems.erase(item);
    }
}

InventoryItem& InventoryManager::GetItemInfo(size_t id)
{
    auto item = std::find_if(m_AvailableItems.begin(), m_AvailableItems.end(), [&id](InventoryItem& item){
        return item.Id == id;
    });

    return *item;
}

void InventoryManager::WriteItemsToSaveData()
{
    int32_t* inventorySaveData = SaveGameManager::GetInstance().GetInventoryItems();
    size_t inventoryIdx;
    for (inventoryIdx = 0; inventoryIdx < m_PlayerItems.size(); inventoryIdx++)
    {
        inventorySaveData[inventoryIdx] = m_PlayerItems[inventoryIdx];
    }

    for (inventoryIdx; inventoryIdx < INVENTORY_ITEMS_SIZE; inventoryIdx++)
    {
        inventorySaveData[inventoryIdx] = -1;
    }
}

void InventoryManager::ReadInventorySaveData()
{
    int32_t* inventorySaveData = SaveGameManager::GetInstance().GetInventoryItems();
    m_PlayerItems.clear();
    for (size_t i = 0; i < INVENTORY_ITEMS_SIZE; i++)
    {
        if(inventorySaveData[i] > 0)
        {
            m_PlayerItems.push_back(inventorySaveData[i]);
        }
    }
}