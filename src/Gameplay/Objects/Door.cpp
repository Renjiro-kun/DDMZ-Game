#include <Defines.h>
#include <Gameplay/Objects/Door.h>
#include <PVRTextureLoader.h>
#include <Gameplay/Inventory/InventoryManager.h>

Door::Door(Vector3 position, size_t itemId, int mapHeight, std::vector<char>* collisionMask)
{
    m_DoorModel = LoadModel("/rd/doorTemp.obj");
    m_DoorTexture = PVRTextureLoader::LoadTexture("/rd/wood.pvr", 0, 0);
    m_DoorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_DoorTexture;
    m_Position = position;
    m_RequiredItemId = itemId;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;

    m_IsOpened = false;

    m_CollisionMaskRef = collisionMask;
    m_MapHeight = mapHeight;
}

Door::~Door()
{
    UnloadTexture(m_DoorTexture);
    UnloadModel(m_DoorModel);
}

void Door::OnDraw3D()
{
    DrawModel(m_DoorModel, m_Position, 1.f, WHITE);
}

void Door::Interact()
{
    if(!m_IsOpened)
    {
        bool itemCheck = InventoryManager::GetInstance().HasItem(m_RequiredItemId);
        if(m_CollisionMaskRef && itemCheck)
        {
            m_CollisionMaskRef->at(m_CellY * m_MapHeight + m_CellX) = 0;
            InventoryManager::GetInstance().UseItem(m_RequiredItemId);
            m_IsOpened = true;
        }
    }
}