#include <Defines.h>
#include <Gameplay/Objects/Door.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <VMU/SaveManager.h>

Door::Door(Vector3 position, size_t itemId, float rotation, int mapHeight, std::vector<char>* collisionMask)
{
    m_DoorOpenRumble.raw = 0x03258710;

    m_DoorModel = &ObjectRepository::GetInstance().GetDoorModel();
    m_Position = position;
    m_RequiredItemId = itemId;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;

    m_IsOpened = false;
    m_Rotation = rotation;

    m_CollisionMaskRef = collisionMask;
    m_MapHeight = mapHeight;
}

Door::~Door()
{
    Unload();
}

void Door::Unload()
{
    
}

void Door::OnDraw3D()
{
    if(m_DoorModel)
    {
        DrawModelEx(*m_DoorModel, m_Position, Vector3{0,1,0}, m_Rotation, Vector3{1,1,1}, WHITE);
    }
}

void Door::OpenDoor()
{
    m_Position.y = 0.87f;
    m_CollisionMaskRef->at(m_CellY * m_MapHeight + m_CellX) = 0;
}

void Door::Interact()
{
    if(!m_IsOpened)
    {
        bool itemCheck = InventoryManager::GetInstance().HasItem(m_RequiredItemId);
        if(m_CollisionMaskRef)
        {
            if(itemCheck)
            {
                InventoryManager::GetInstance().UseItem(m_RequiredItemId);
                m_IsOpened = true;
                OpenDoor();
                SFXManager::GetInstance().Play(ObjectRepository::GetInstance().GetDoorOpenSFX());
                PuruPuruManager::GetInstance().Rumble(m_DoorOpenRumble);
                m_Context->currentInteractableState->State = true;
            }
            else
            {
                InventoryItem& item = InventoryManager::GetInstance().GetItemInfo(m_RequiredItemId);
                MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::ItemRequired, SystemMessageType::Default, 0.f, item.name.c_str());
            }
        }
    }   
}