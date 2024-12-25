#include <Defines.h>
#include <Gameplay/Objects/ItemChest.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>
#include <VMU/SaveManager.h>

ItemChest::ItemChest(Vector3 position, size_t itemId)
{
    m_ChestModel = &ObjectRepository::GetInstance().GetChestModel();
    m_Position = position;
    m_ItemId = itemId;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;

    m_IsOpened = false;
}

void ItemChest::OnDraw3D()
{
    if(m_ChestModel)
    {
        DrawModel(*m_ChestModel, m_Position, 1.f, WHITE);
    }
}

void ItemChest::Interact()
{
    if(m_ItemId > 0 && !m_IsOpened)
    {
        InventoryManager::GetInstance().AddItem(m_ItemId);
        InventoryItem& item = InventoryManager::GetInstance().GetItemInfo(m_ItemId);
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::FoundItem, SystemMessageType::Default, 0.f, item.name.c_str());
        m_IsOpened = true;
        SFXManager::GetInstance().Play(ObjectRepository::GetInstance().GetItemPickupSFX());
        m_Context->currentInteractableState->State = true;
    }
    else
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::EmptyChest);
    }
}

void ItemChest::Unload()
{
    
}

ItemChest::~ItemChest()
{
    Unload();
}