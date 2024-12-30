#include <Defines.h>
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
        wav_volume(bgm, m_CurrentVolume);
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

int BGMManager::GetVolume()
{
    return roundf(((float)m_CurrentVolume / 255) * 100);
}

void BGMManager::SetVolume(int volume)
{
    m_CurrentVolume = ((float)volume / 100) * 255;
}