#pragma once
#include <raylib/raylib.h>
#include <Gameplay/Objects/Interactable.h>

class SavePoint : public Interactable
{
public:
    SavePoint(Vector3 position);
    ~SavePoint();
public:
    void Interact();

    void OnDraw3D();

    void Unload() override;

private:
    Model m_SavePointModel;
    Texture2D m_SavePointTexture;

    Vector3 m_Position;
};