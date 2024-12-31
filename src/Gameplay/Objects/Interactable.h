#pragma once
#include <raylib/raylib.h>

struct InteractableInfo;

struct InteractableContext
{
    int playerPosX;
    int playerPosY;
    int levelIdx;
    float currentTimeLimit;
    InteractableInfo* currentInteractableState;
};

class Interactable
{
public:
    virtual void Interact() = 0;
    virtual void OnDraw3D() = 0;

    virtual void Unload() = 0;
    virtual void SetState(bool state) {}

    bool IsOnCell(int x, int y)
    {
        return m_CellX == x && m_CellY == y;
    }

    void SetContext(InteractableContext* ctx) { m_Context = ctx; }

    const Vector3& GetPosition() { return m_Position; }

protected:
    Vector3 m_Position;
    InteractableContext* m_Context;

    int m_CellX = 0;
    int m_CellY = 0;
};