#include <Defines.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <PVRTextureLoader.h>

void ObjectRepository::Init()
{

}

void ObjectRepository::Shutdown()
{

}


void ObjectRepository::OnActivate()
{
    m_WoodTexture = PVRTextureLoader::LoadTexture(GET_ASSET_FROM_RD("wood.pvr"), 0, 0);
    m_DoorModel = LoadModel(GET_ASSET_FROM_RD("Door.obj"));
    m_DoorModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_WoodTexture;

    m_ChestModel = LoadModel(GET_ASSET_FROM_RD("ItemChest.obj"));
    m_ChestModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_WoodTexture;

    m_SavePointModel = LoadModel(GET_ASSET_FROM_RD("SavePoint.obj"));
    m_SavePointModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_WoodTexture;
}

void ObjectRepository::OnDeactivate()
{
    UnloadTexture(m_WoodTexture);
    UnloadModel(m_ChestModel);
    UnloadModel(m_DoorModel);
    UnloadModel(m_SavePointModel);
}