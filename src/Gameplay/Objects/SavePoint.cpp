#include <pch.h>
#include <Gameplay/Objects/SavePoint.h>
#include <PVRTextureLoader.h>

SavePoint::SavePoint(Vector3 position)
{
    m_SavePointModel = LoadModel("/rd/table.obj");
    m_SavePointTexture = PVRTextureLoader::LoadTexture("/rd/wood.pvr", 0, 1);
    m_SavePointModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_SavePointTexture;
    m_Position = position;
}

void SavePoint::OnDraw3D()
{
    DrawModel(m_SavePointModel, m_Position, 1.f, WHITE);
}

void SavePoint::Interact()
{
    
}

SavePoint::~SavePoint()
{
    UnloadTexture(m_SavePointTexture);
    UnloadModel(m_SavePointModel);
}