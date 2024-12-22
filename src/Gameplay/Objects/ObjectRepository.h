#pragma once
#include <raylib/raylib.h>

class ObjectRepository
{
public:
    static ObjectRepository& GetInstance()
    {
        static ObjectRepository instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void OnActivate();
    void OnDeactivate();
public:
    Model& GetChestModel() { return m_ChestModel; }
    Model& GetDoorModel() { return m_DoorModel; }
    Model& GetSavePointModel() { return m_SavePointModel; }

private:
    ObjectRepository() = default;
    ~ObjectRepository() = default;
    ObjectRepository(const ObjectRepository&) = delete;
    ObjectRepository& operator=(const ObjectRepository&) = delete;
private:
    Model m_ChestModel;
    Model m_DoorModel;
    Model m_SavePointModel;

    Texture m_WoodTexture;
};