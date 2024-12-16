#include <Defines.h>
#include <Gameplay/Inventory/InventoryManager.h>
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