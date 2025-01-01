#include <Defines.h>

#include <Scene/ScenesImpl/SceneOptions.h>
#include <Scene/SceneManager.h>
#include <Sound/SfxManager.h>
#include <Sound/BgmManager.h>
#include <VMU/PuruPuruManager.h>
#include <VMU/SaveManager.h>
#include <UI/Button.h>
#include <UI/Toggle.h>
#include <UI/Slider.h>

void OnBackPressed();
void OnVibrationPressed(Toggle* sender);
void OnVibrationFocussed(Toggle* sender);
bool GetVibrationValue();
void SetVibrationValue(bool value);

void SetSFXVolume(int value);
int GetSFXVolume();

void SetBGMVolume(int value);
int GetBGMVolume();

void SaveOptions();

void SceneOptions::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_MenuCanvas = new Canvas(InputContext::Default);
    m_MenuCanvas->SetActive(true);
    m_MenuCanvas->AddWidget(new Slider(Vector2{150, 150}, "BGM VOLUME ", 5, 0, 100, SetBGMVolume, GetBGMVolume));
    m_MenuCanvas->AddWidget(new Slider(Vector2{150, 200}, "SFX VOLUME ", 5, 0, 100, SetSFXVolume, GetSFXVolume));
    m_MenuCanvas->AddWidget(new Toggle(Vector2{150, 250}, "VIBRATION ", OnVibrationPressed, OnVibrationFocussed, SetVibrationValue, GetVibrationValue));
    m_MenuCanvas->AddWidget(new Button(Vector2{150, 300}, "SAVE OPTIONS", SaveOptions));
    m_MenuCanvas->AddWidget(new Button(Vector2{150, 350}, "BACK", OnBackPressed));

    m_BackTexture = new Texture2D[widthCount * heightCount];
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
            m_BackTexture[y*widthCount+x] = LoadTexture(TextFormat(GET_ASSET_FROM_CD("titlescreen/BG_TS_%01i%01i.png"), y+1, x+1));
        }
    }

    m_SceneBGM = BGMManager::GetInstance().LoadSound(GET_ASSET_FROM_CD("music/bgm_menu.adpcm"));
    BGMManager::GetInstance().Play(m_SceneBGM);
}

void SceneOptions::OnDectivated()
{
    BGMManager::GetInstance().Stop(m_SceneBGM);
    BGMManager::GetInstance().UnloadBGM(m_SceneBGM);
    
    for (size_t i = 0; i < heightCount * widthCount; i++)
    {
        UnloadTexture(m_BackTexture[i]);
    }
    
    delete[] m_BackTexture;
    delete m_MenuCanvas;
}

void SceneOptions::OnDraw3D()
{

}

void SceneOptions::OnDraw2D()
{
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
           DrawTexture(m_BackTexture[y*widthCount+x], x * 256, y * 256, WHITE);
        }
    }

    m_MenuCanvas->OnDraw2D();
}

void SceneOptions::OnUpdate()
{
    m_MenuCanvas->OnUpdate();
}

void OnBackPressed()
{
    // TODO: Add save
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAIN_MENU);
}

void OnVibrationPressed(Toggle* sender)
{
    SaveGameManager::GetInstance().SetUseVibration(PuruPuruManager::GetInstance().GetEnable());
}

void OnVibrationFocussed(Toggle* sender)
{

}

bool GetVibrationValue()
{
    return PuruPuruManager::GetInstance().GetEnable();   
}

void SetVibrationValue(bool value)
{
    PuruPuruManager::GetInstance().SetEnable(value);
}

void SetSFXVolume(int value)
{
    SaveGameManager::GetInstance().SetSFXVolume(value);
    SFXManager::GetInstance().SetCurrentVolume(value);
}

int GetSFXVolume()
{
    return SFXManager::GetInstance().GetCurrentVolume();
}

void SetBGMVolume(int value)
{
    SaveGameManager::GetInstance().SetBGMVolume(value);
    BGMManager::GetInstance().SetVolume(value);
}

int GetBGMVolume()
{
    return BGMManager::GetInstance().GetVolume();
}

void SaveOptions()
{
    SaveGameManager::GetInstance().SaveData();
}