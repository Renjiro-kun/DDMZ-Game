#pragma once
#include <raylib/raylib.h>
#include <Sound/SfxManager.h>

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

    SFXHandle GetDoorOpenSFX() { return m_DoorOpenSFX; }
    SFXHandle GetItemPickupSFX() { return m_ItemPickupSFX; }
    SFXHandle GetSavePointSFX() { return m_SavePointSFX; }

private:
    ObjectRepository() = default;
    ~ObjectRepository() = default;
    ObjectRepository(const ObjectRepository&) = delete;
    ObjectRepository& operator=(const ObjectRepository&) = delete;
private:
    Model m_ChestModel;
    Model m_DoorModel;
    Model m_SavePointModel;

    Texture m_DoorTexture;
    Texture m_SavePointTexture;
    Texture m_ItemChestTexture;

    SFXHandle m_DoorOpenSFX;
    SFXHandle m_ItemPickupSFX;
    SFXHandle m_SavePointSFX;
};