#include <VMU/PuruPuruManager.h>
#include <dc/maple/controller.h>
#include <dc/maple/purupuru.h>
#include <VMU/SaveManager.h>

maple_device_t* PuruPuruManager::m_PuruPuruDevice = nullptr;

void PuruPuruManager::Init()
{
    if((m_PuruPuruDevice == NULL) || (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) == 0)) 
    {
        m_PuruPuruDevice = maple_enum_type(0, MAPLE_FUNC_PURUPURU);
        m_IsEnabled = SaveGameManager::GetInstance().GetUseVibration();
    }
    else
    {
        m_IsEnabled = false;
    }

}

void PuruPuruManager::Shutdown()
{
    if((m_PuruPuruDevice != NULL) && (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) != 0))  
        purupuru_rumble_raw(m_PuruPuruDevice, 0x00000000);
}

void PuruPuruManager::SetEnable(bool value)
{
    if((m_PuruPuruDevice != NULL) && (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) != 0))  
    {
        m_IsEnabled = value;
    }
    else
    {
        m_IsEnabled = false;
    }
}

void PuruPuruManager::Rumble(rumble_fields_t effect)
{
    if((m_PuruPuruDevice != NULL) && (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) != 0) && m_IsEnabled)  
        purupuru_rumble_raw(m_PuruPuruDevice, effect.raw);
}