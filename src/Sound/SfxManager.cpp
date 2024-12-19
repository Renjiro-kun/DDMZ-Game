#include <Sound/SfxManager.h>
#include <dc/sound/sound.h>
#include <dc/sound/sfxmgr.h>

void SFXManager::Init()
{
    snd_init();
}

void SFXManager::Shutdown()
{
    snd_shutdown();
}

void SFXManager::Play(SFXHandle sfx)
{
    // TODO: Add pan and volume config
    if(sfx != SFXHND_INVALID)
    {
        snd_sfx_play(sfx, 255, 128);
    }
}

SFXHandle SFXManager::LoadSFX(const std::string& path)
{
    SFXHandle retValue = snd_sfx_load(path.c_str());
    return retValue;
}

void SFXManager::Unload(SFXHandle sfx)
{
    if(sfx != SFXHND_INVALID)
    {
        snd_sfx_unload(sfx);
    }
}