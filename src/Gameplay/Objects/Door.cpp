#include <Defines.h>
#include <Gameplay/Objects/Door.h>
#include <PVRTextureLoader.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>

Door::Door(Vector3 position, size_t itemId, float rotation, int mapHeight, std::vector<char>* collisionMask)
{
    m_DoorModel = LoadModel("/rd/Door.obj");
    m_DoorTexture = PVRTextureLoader::LoadTexture("/rd/wood.pvr", 0, 0);
    m_DoorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_DoorTexture;
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
    UnloadTexture(m_DoorTexture);
    UnloadModel(m_DoorModel);
}

void Door::OnDraw3D()
{
    DrawModelEx(m_DoorModel, m_Position, Vector3{0,1,0}, m_Rotation, Vector3{1,1,1}, WHITE);
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
                m_CollisionMaskRef->at(m_CellY * m_MapHeight + m_CellX) = 0;
                InventoryManager::GetInstance().UseItem(m_RequiredItemId);
                m_Position.y = 0.87f;
                m_IsOpened = true;
            }
            else
            {
                InventoryItem& item = InventoryManager::GetInstance().GetItemInfo(m_RequiredItemId);
                MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::ItemRequired, SystemMessageType::Default, 0.f, item.name.c_str());
            }
        }
    }
}