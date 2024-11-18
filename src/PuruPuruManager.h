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

private:
    PuruPuruManager() = default;
    ~PuruPuruManager() = default;
    PuruPuruManager(const PuruPuruManager&) = delete;
    PuruPuruManager& operator=(const PuruPuruManager&) = delete;
private:
    static maple_device_t* m_PuruPuruDevice;
};