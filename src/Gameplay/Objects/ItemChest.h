#pragma once
#include <Gameplay/Objects/Interactable.h>
#include <raylib/raylib.h>

class ItemChest : public Interactable
{
public:
    ItemChest(Vector3 position, float rotation, size_t itemId);
    ~ItemChest();

public:
    void Interact() override;
    void OnDraw3D() override;
    
    void Unload() override;

    void SetState(bool state) { m_IsOpened = state; }

private:
    Model* m_ChestModel;
    size_t m_ItemId;
    float m_Rotation;

    bool m_IsOpened;
};