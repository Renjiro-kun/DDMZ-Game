#include <PuruPuruManager.h>
#include <dc/maple/controller.h>
#include <dc/maple/purupuru.h>

maple_device_t* PuruPuruManager::m_PuruPuruDevice = nullptr;

inline void word2hexbytes(uint32_t word, uint8_t *bytes) {
  for (int i = 0; i < 8; i++) {
    bytes[i] = (word >> (28 - (i * 4))) & 0xf;
  }
}

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