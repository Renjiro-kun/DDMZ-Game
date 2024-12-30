#pragma once
#include <dc/maple.h>
#include <cstdint>


class PuruPuruManager
{
public:
    static PuruPuruManager& GetInstance()
    {
        static PuruPuruManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void Rumble(uint32_t effect);
    void SetEnable(bool value);
    bool GetEnable() { return m_IsEnabled; }

private:
    PuruPuruManager() = default;
    ~PuruPuruManager() = default;
    PuruPuruManager(const PuruPuruManager&) = delete;
    PuruPuruManager& operator=(const PuruPuruManager&) = delete;
private:
    bool m_IsEnabled = false;
    static maple_device_t* m_PuruPuruDevice;
};