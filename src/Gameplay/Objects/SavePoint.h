#pragma once
#include <raylib/raylib.h>

class SavePoint
{
public:
    SavePoint(Vector3 position);
    ~SavePoint();
public:
    void Interact();

    void OnDraw3D();

private:
    Model m_SavePointModel;
    Texture2D m_SavePointTexture;

    Vector3 m_Position;
};