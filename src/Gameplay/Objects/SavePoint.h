#pragma once
#include <raylib/raylib.h>
#include <Gameplay/Objects/Interactable.h>
#include <VMU/PuruPuruManager.h>

class SavePoint : public Interactable
{
public:
    SavePoint(Vector3 position, float rotation);
    ~SavePoint();
public:
    void Interact();

    void OnDraw3D();

    void Unload() override;

private:
    rumble_fields_t m_SaveRumble;
    Model* m_SavePointModel;

    float m_Rotation;
};