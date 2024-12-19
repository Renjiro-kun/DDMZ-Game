#pragma once
#include <Gameplay/Objects/Interactable.h>
#include <raylib/raylib.h>

class ItemChest : public Interactable
{
public:
    ItemChest(Vector3 position, size_t itemId);
    ~ItemChest();

public:
    void Interact() override;
    void OnDraw3D() override;

private:
    Model m_ChestModel;
    Texture2D m_ChestTexture;
    Vector3 m_Position;
    size_t m_ItemId;

    bool m_IsOpened;
};