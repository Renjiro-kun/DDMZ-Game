#include <Sound/BgmManager.h>

#include <dc/sound/stream.h>
#include <wav/sndwav.h>

void BGMManager::Init()
{
    snd_stream_init();
    wav_init();
}

void BGMManager::Shutdown()
{
    wav_shutdown();
    snd_stream_shutdown();
}

BGM_Handle BGMManager::LoadSound(const std::string& path)
{
    return wav_create(path.c_str(), 1);
}

void BGMManager::Play(BGM_Handle bgm)
{
    if(bgm != INVALID_BGM_HANDLE)
    {
        wav_play(bgm);
    }
}

void BGMManager::SetVolume(BGM_Handle bgm, int volume)
{
    if(bgm != INVALID_BGM_HANDLE)
    {
        wav_volume(bgm, volume);
    }
}

void BGMManager::Stop(BGM_Handle bgm)
{
    if(bgm != INVALID_BGM_HANDLE)
    {
        wav_stop(bgm);
    }
}

void BGMManager::UnloadBGM(BGM_Handle bgm)
{
    if(bgm != INVALID_BGM_HANDLE)
    {
        wav_destroy(bgm);
    }
}