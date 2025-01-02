#include <Defines.h>
#include <Gameplay/Objects/ItemChest.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>
#include <VMU/SaveManager.h>

ItemChest::ItemChest(Vector3 position, float rotation, size_t itemId)
{
    m_ChestOpenRumble.raw = 0x01083810;
    m_ChestModel = &ObjectRepository::GetInstance().GetChestModel();
    m_Position = position;
    m_ItemId = itemId;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;

    m_IsOpened = false;
    m_Rotation = rotation;
}

void ItemChest::OnDraw3D()
{
    if(m_ChestModel)
    {
        DrawModelEx(*m_ChestModel, m_Position, Vector3{0,1,0}, m_Rotation, Vector3{1,1,1}, WHITE);
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
        PuruPuruManager::GetInstance().Rumble(m_ChestOpenRumble);
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