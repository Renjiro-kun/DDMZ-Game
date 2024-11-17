#pragma once
#include <string>

typedef int BGM_Handle;

class BGMManager
{
public:
    static BGMManager& GetInstance()
    {
        static BGMManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    BGM_Handle LoadSound(const std::string& path);
    void UnloadBGM(BGM_Handle bgm);
    void SetVolume(BGM_Handle bgm, int volume);
    void Play(BGM_Handle bgm);
    void Stop(BGM_Handle bgm);
private:
    BGMManager() = default;
    ~BGMManager() = default;
    BGMManager(const BGMManager&) = delete;
    BGMManager& operator=(const BGMManager&) = delete;
};