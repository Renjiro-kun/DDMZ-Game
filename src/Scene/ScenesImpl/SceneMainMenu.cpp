#include <Defines.h>
#include <Scene/SceneManager.h>
#include <Scene/ScenesImpl/SceneMainMenu.h>
#include <VMU/SaveManager.h>

#include <UI/Button.h>

void OnContinuePressed();
void OnNewGamePressed();
void OnOptionsPressed();

void SceneMainMenu::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_MenuCanvas = new Canvas(InputContext::Default);
    m_MenuCanvas->SetActive(true);
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 200}, "CONTINUE", OnContinuePressed));
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 250}, "NEW GAME", OnNewGamePressed));
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 300}, "OPTIONS", OnOptionsPressed));

    m_AdvTextures = new Texture2D[widthCount * heightCount];
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
            m_AdvTextures[y*widthCount+x] = LoadTexture(TextFormat(GET_ASSET_FROM_CD("titlescreen/BG_TS_%01i%01i.png"), y+1, x+1));
        }
    }
    
    m_SceneBGM = BGMManager::GetInstance().LoadSound(GET_ASSET_FROM_CD("music/bgm_menu.adpcm"));
    BGMManager::GetInstance().Play(m_SceneBGM);
}

void SceneMainMenu::OnDectivated()
{
    BGMManager::GetInstance().Stop(m_SceneBGM);
    BGMManager::GetInstance().UnloadBGM(m_SceneBGM);

    for (size_t i = 0; i < heightCount * widthCount; i++)
    {
        UnloadTexture(m_AdvTextures[i]);
    }

    m_MenuCanvas->SetActive(false);
    delete[] m_AdvTextures;
    delete m_MenuCanvas;
}

void SceneMainMenu::OnDraw3D()
{

}

void SceneMainMenu::OnDraw2D()
{
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
           DrawTexture(m_AdvTextures[y*widthCount+x], x * 256, y * 256, WHITE);
        }
    }

    m_MenuCanvas->OnDraw2D();
}

void SceneMainMenu::OnUpdate()
{
    m_MenuCanvas->OnUpdate();
}

void OnContinuePressed()
{
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAZE);
}

void OnNewGamePressed()
{
    SaveGameManager::GetInstance().ResetSaveGame();
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_MAZE);
}

void OnOptionsPressed()
{
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_OPTIONS);
}