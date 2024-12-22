#pragma once
#include <Gameplay/Objects/Interactable.h>
#include <raylib/raylib.h>
#include <vector>

class Door : public Interactable
{
public:
    Door(Vector3 position, size_t itemId, float rotation, int mapWidth, std::vector<char>* collisionMask);
    ~Door();

public:
    void Interact() override;
    void OnDraw3D() override;

    void Unload() override;

private:
    Model* m_DoorModel = nullptr;
    Vector3 m_Position;
    size_t m_RequiredItemId;
    std::vector<char>* m_CollisionMaskRef;
    int m_MapHeight;
    float m_Rotation;

    bool m_IsOpened;
};