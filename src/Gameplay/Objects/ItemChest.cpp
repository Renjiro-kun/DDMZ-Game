#include <Defines.h>
#include <Gameplay/Objects/ItemChest.h>
#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>
#include <PVRTextureLoader.h>

ItemChest::ItemChest(Vector3 position, size_t itemId)
{
    m_ChestModel = LoadModel("/rd/cube.obj");
    m_ChestTexture = PVRTextureLoader::LoadTexture("/rd/wood.pvr", 0, 0);
    m_ChestModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_ChestTexture;
    m_Position = position;
    m_ItemId = itemId;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;
}

void ItemChest::OnDraw3D()
{
    DrawModel(m_ChestModel, m_Position, 1.f, WHITE);
}

void ItemChest::Interact()
{
    if(m_ItemId > 0)
    {
        InventoryManager::GetInstance().AddItem(m_ItemId);
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::FoundItem);
    }
}

ItemChest::~ItemChest()
{
    UnloadTexture(m_ChestTexture);
    UnloadModel(m_ChestModel);
}