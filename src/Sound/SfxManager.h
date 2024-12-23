#pragma once
#include <string>

typedef uint32_t SFXHandle;

class SFXManager
{
public:
    static SFXManager& GetInstance()
    {
        static SFXManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    SFXHandle LoadSFX(const std::string& path);

    void Play(SFXHandle sfx);

    void Unload(SFXHandle sfx);

    int GetCurrentVolume();
    void SetCurrentVolume(int volume);
private:
    SFXManager() = default;
    ~SFXManager() = default;
    SFXManager(const SFXManager&) = delete;
    SFXManager& operator=(const SFXManager&) = delete;
private:
    int m_CurrentVolume{255};
};