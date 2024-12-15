#include <Defines.h>
#include <VMU/SaveManager.h>
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
    vmu_pkg_t pkg;
    int pkg_size;
    uint8_t* pkg_out;
    file_t f;

    strcpy(pkg.desc_short, SHORT_DESC);
    strcpy(pkg.desc_long, LONG_DESC);
    strcpy(pkg.app_id, APP_ID);
    pkg.icon_cnt = 0;
    pkg.icon_anim_speed = 0;
    pkg.eyecatch_type = VMUPKG_EC_NONE;
    pkg.data_len = sizeof(SaveDataPkg);
    pkg.data = reinterpret_cast<uint8_t*>(&m_CurrentSaveData);

    vmu_pkg_build(&pkg, &pkg_out, &pkg_size);

    fs_unlink(TextFormat("/vmu/a1/%s", SAVE_NAME));
    f = fs_open(TextFormat("/vmu/a1/%s", SAVE_NAME), O_WRONLY);

    if(!f)
    {
        // show error message
        return;
    }

    MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::SaveData, SystemMessageType::Timed, 2.f);

    fs_write(f, pkg_out, pkg_size);
    fs_close(f);
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
        // Add error message
        return;
    }
    pkg_size = fs_total(f);
    if(pkg_size <= 0)
    {
        // Add error message
        return;
    }
    MessageManager::GetInstance().RequestSystemMessage(SystemMessageID::LoadData, SystemMessageType::Timed, 2.f);

    pkg_data = (uint8_t*)malloc(pkg_size);
    fs_read(f, pkg_data, pkg_size);
    vmu_pkg_parse(pkg_data, &pkg);

    const SaveDataPkg* ingamePkg = reinterpret_cast<const SaveDataPkg*>(pkg.data);

    m_CurrentSaveData.LevelIdx = ingamePkg->LevelIdx;

    free(pkg_data);
}