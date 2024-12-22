#include <Defines.h>
#include <Gameplay/Objects/SavePoint.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <VMU/SaveManager.h>

SavePoint::SavePoint(Vector3 position, float rotation)
{
    m_SavePointModel = &ObjectRepository::GetInstance().GetSavePointModel();
    m_Position = position;

    m_CellX = (int)position.x;
    m_CellY = (int)position.z;
    m_Rotation = rotation;
}

void SavePoint::OnDraw3D()
{
    if(m_SavePointModel)
    {
        DrawModelEx(*m_SavePointModel, m_Position, Vector3{0,1,0}, m_Rotation, Vector3{1,1,1}, WHITE);
    }
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

}

SavePoint::~SavePoint()
{
    Unload();
}