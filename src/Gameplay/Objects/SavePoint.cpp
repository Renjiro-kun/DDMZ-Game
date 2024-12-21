#include <Defines.h>
#include <Gameplay/Objects/SavePoint.h>
#include <PVRTextureLoader.h>
#include <VMU/SaveManager.h>

SavePoint::SavePoint(Vector3 position, float rotation)
{
    m_SavePointModel = LoadModel("/rd/SavePoint.obj");
    m_SavePointTexture = PVRTextureLoader::LoadTexture("/rd/wood.pvr", 0, 0);
    m_SavePointModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_SavePointTexture;
    m_Position = position;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;
    m_Rotation = rotation;
}

void SavePoint::OnDraw3D()
{
    DrawModelEx(m_SavePointModel, m_Position, Vector3{0,1,0}, m_Rotation, Vector3{1,1,1}, WHITE);
}

void SavePoint::Interact()
{
    if(m_Context)
    {
        SaveGameManager::GetInstance().SetCurrentLevel(m_Context->levelIdx);
        SaveGameManager::GetInstance().SetPlayerPositionX(m_Context->playerPosX);
        SaveGameManager::GetInstance().SetPlayerPositionY(m_Context->playerPosY);
        SaveGameManager::GetInstance().SaveData();
    }
}

void SavePoint::Unload()
{
    UnloadTexture(m_SavePointTexture);
    UnloadModel(m_SavePointModel);
}

SavePoint::~SavePoint()
{
    Unload();
}