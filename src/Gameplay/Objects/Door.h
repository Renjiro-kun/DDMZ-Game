#pragma once
#include <Gameplay/Objects/Interactable.h>
#include <raylib/raylib.h>
#include <vector>

class Door : public Interactable
{
public:
    Door(Vector3 position, size_t itemId, int mapHeight, std::vector<char>* collisionMask);
    ~Door();

public:
    void Interact() override;
    void OnDraw3D() override;

private:
    Model m_DoorModel;
    Texture2D m_DoorTexture;
    Vector3 m_Position;
    size_t m_RequiredItemId;
    std::vector<char>* m_CollisionMaskRef;
    int m_MapHeight;

    bool m_IsOpened;
};