#include <PuruPuruManager.h>
#include <dc/maple/controller.h>
#include <dc/maple/purupuru.h>

maple_device_t* PuruPuruManager::m_PuruPuruDevice = nullptr;

void PuruPuruManager::Init()
{
    if((m_PuruPuruDevice == NULL) || (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) == 0)) 
    {
        m_PuruPuruDevice = maple_enum_type(0, MAPLE_FUNC_PURUPURU);
    }
}

void PuruPuruManager::Shutdown()
{
    if((m_PuruPuruDevice != NULL) && (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) != 0))  
        purupuru_rumble_raw(m_PuruPuruDevice, 0x00000000);
}

void PuruPuruManager::Rumble(uint32_t effect)
{
    if((m_PuruPuruDevice != NULL) && (maple_dev_valid(m_PuruPuruDevice->port, m_PuruPuruDevice->unit) != 0))  
        purupuru_rumble_raw(m_PuruPuruDevice, effect);
}