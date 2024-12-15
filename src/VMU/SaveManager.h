#pragma once

#define APP_ID "DDMZ"
#define SAVE_NAME "DDSAVE"
#define LONG_DESC "DreamDisc 24 Game"
#define SHORT_DESC "DDGAME"

struct SaveDataPkg
{
    SaveDataPkg()
    {
        LevelIdx = 0;
        PositionX = 0;
        PositionY = 0;
        BGMVolume = 255;
        SFXVolume = 255;
        UseVibration = false;
    }

    uint16_t LevelIdx = 0;
    int32_t PositionX = 0;
    int32_t PositionY = 0;
    int32_t BGMVolume = 255;
    int32_t SFXVolume = 255;
    bool UseVibration = false;
};


class SaveGameManager
{
public:
    static SaveGameManager& GetInstance()
    {
        static SaveGameManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void SaveData();
    void LoadData();
public:
    void SetCurrentLevel(uint16_t lvlIdx){ m_CurrentSaveData.LevelIdx = lvlIdx; }
    int16_t GetCurrentLevel() const { return m_CurrentSaveData.LevelIdx; }

    bool GetUseVibration() { return m_CurrentSaveData.UseVibration; }
    void SetUseVibration(bool value) { m_CurrentSaveData.UseVibration = value; }

    void SetPlayerPositionX(int value) { m_CurrentSaveData.PositionX = value; }
    void SetPlayerPositionY(int value) { m_CurrentSaveData.PositionY = value; }

    int GetPlayerPositionX() { return m_CurrentSaveData.PositionX; }
    int GetPlayerPositionY() { return m_CurrentSaveData.PositionY; }

    void ResetSaveGame();
    void ResetOptions();
private:
    SaveGameManager() = default;
    ~SaveGameManager() = default;
    SaveGameManager(const SaveGameManager&) = delete;
    SaveGameManager& operator=(const SaveGameManager&) = delete;
private:
    static SaveDataPkg m_CurrentSaveData;
};