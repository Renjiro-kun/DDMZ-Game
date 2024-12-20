#pragma once

struct InteractableContext
{
    int playerPosX;
    int playerPosY;
    int levelIdx;
};

class Interactable
{
public:
    virtual void Interact() = 0;
    virtual void OnDraw3D() = 0;

    virtual void Unload() = 0;

    bool IsOnCell(int x, int y)
    {
        return m_CellX == x && m_CellY == y;
    }

    void SetContext(InteractableContext* ctx) { m_Context = ctx; }

protected:
    InteractableContext* m_Context;

    int m_CellX = 0;
    int m_CellY = 0;
};