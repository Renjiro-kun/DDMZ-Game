#include <Defines.h>
#include <VMU/SaveManager.h>

#include <Gameplay/Inventory/InventoryManager.h>
#include <Messages/MessageManager.h>

#include <kos.h>

SaveDataPkg SaveGameManager::m_CurrentSaveData;

void SaveGameManager::Init()
{
    m_CurrentSaveData = SaveDataPkg();

}

void SaveGameManager::Shutdown()
{

}

void SaveGameManager::SaveData()
{
    InventoryManager::GetInstance().WriteItemsToSaveData();
    vmu_pkg_t pkg;
    int pkg_size;
    uint8_t* pkg_out;
    file_t f;

    strcpy(pkg.desc_short, SHORT_DESC);
    strcpy(pkg.desc_long, LONG_DESC);
    strcpy(pkg.app_id, APP_ID);
    pkg.icon_cnt = 1;
    pkg.icon_data = VMU_SAVE_ICON;
    memcpy(&pkg.icon_pal[0], VMU_SAVE_ICON_PALLETE,32);
    pkg.icon_anim_speed = 0;
    pkg.eyecatch_type = VMUPKG_EC_NONE;
    pkg.data_len = sizeof(SaveDataPkg);
    pkg.data = reinterpret_cast<uint8_t*>(&m_CurrentSaveData);

    int res = vmu_pkg_build(&pkg, &pkg_out, &pkg_size);
    if(res < 0)
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::SaveFailed, SystemMessageType::Timed, 2.f);
        return;
    }

    res = fs_unlink(TextFormat("/vmu/a1/%s", SAVE_NAME));
    f = fs_open(TextFormat("/vmu/a1/%s", SAVE_NAME), O_WRONLY);

    if(!f)
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::SaveFailed, SystemMessageType::Timed, 2.f);
        return;
    }

    res = fs_write(f, pkg_out, pkg_size);
    fs_close(f);
    if(res < 0)
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::SaveFailed, SystemMessageType::Timed, 2.f);
        return;
    }

    MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::SaveData, SystemMessageType::Timed, 2.f);
}

void SaveGameManager::LoadData()
{
    vmu_pkg_t pkg;
    int pkg_size;
    uint8_t* pkg_data;
    file_t f;

    f = fs_open(TextFormat("/vmu/a1/%s", SAVE_NAME), O_RDONLY);
    if(!f)
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::LoadFailed, SystemMessageType::Timed, 2.f);
        return;
    }
    pkg_size = fs_total(f);
    if(pkg_size <= 0)
    {
        MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::LoadFailed, SystemMessageType::Timed, 2.f);
        return;
    }
    MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::LoadData, SystemMessageType::Timed, 2.f);

    pkg_data = (uint8_t*)malloc(pkg_size);
    fs_read(f, pkg_data, pkg_size);
    vmu_pkg_parse(pkg_data, &pkg);

    const SaveDataPkg* ingamePkg = reinterpret_cast<const SaveDataPkg*>(pkg.data);
    CopyDataFromVMUPkg(ingamePkg);
    InventoryManager::GetInstance().ReadInventorySaveData();

    free(pkg_data);
}

void SaveGameManager::CopyDataFromVMUPkg(const SaveDataPkg* pkg)
{
    m_CurrentSaveData.LevelIdx = pkg->LevelIdx;
    m_CurrentSaveData.PositionX = pkg->PositionX;
    m_CurrentSaveData.PositionY = pkg->PositionY;
    m_CurrentSaveData.TimeLimit = pkg->TimeLimit;
    m_CurrentSaveData.UseVibration = pkg->UseVibration;
    m_CurrentSaveData.SFXVolume = pkg->SFXVolume;
    m_CurrentSaveData.BGMVolume = pkg->BGMVolume;
    for (size_t i = 0; i < INTERACTABLE_STATES_SIZE; i++)
    {
        m_CurrentSaveData.InteractableStates[i].CellX = pkg->InteractableStates[i].CellX;
        m_CurrentSaveData.InteractableStates[i].CellY = pkg->InteractableStates[i].CellY;
        m_CurrentSaveData.InteractableStates[i].State = pkg->InteractableStates[i].State;
    }
    for (size_t i = 0; i < INVENTORY_ITEMS_SIZE; i++)
    {
        m_CurrentSaveData.InventoryItems[i] = pkg->InventoryItems[i];
    }
}

void SaveGameManager::ResetOptions()
{
    m_CurrentSaveData.BGMVolume = 100;
    m_CurrentSaveData.SFXVolume = 100;
    m_CurrentSaveData.UseVibration = false;
}

void SaveGameManager::ResetSaveGame()
{
    m_CurrentSaveData.LevelIdx = 0;
    m_CurrentSaveData.PositionX = 0;
    m_CurrentSaveData.PositionY = 0;
    m_CurrentSaveData.TimeLimit = -1.f;
    InventoryManager::GetInstance().ResetInventory();
    for (size_t i = 0; i < INVENTORY_ITEMS_SIZE; i++)
    {
        m_CurrentSaveData.InventoryItems[i] = -1;
    }
    ResetInteractableStates();
    SaveGameManager::GetInstance().SaveData();
    // HACK
    InputContextManager::GetInstance().SetInputContext(InputContext::Message);
}

void SaveGameManager::ResetInteractableStates()
{
    for (size_t i = 0; i < INTERACTABLE_STATES_SIZE; i++)
    {
        m_CurrentSaveData.InteractableStates[i].CellX = -1;
        m_CurrentSaveData.InteractableStates[i].CellY = -1;
        m_CurrentSaveData.InteractableStates[i].State = false;
    }
}