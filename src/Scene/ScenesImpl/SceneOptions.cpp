#include <Defines.h>
#include <Scene/ScenesImpl/SceneOptions.h>
#include <Scene/SceneManager.h>

#include <UI/Button.h>

void OnBackPressed();

void SceneOptions::OnActivated()
{
    m_Camera.position = Vector3{0.f, 0.f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;

    m_MenuCanvas = new Canvas(InputContext::Default);
    m_MenuCanvas->SetActive(true);
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 200}, "VOLUME "));
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 250}, "VIBRATION "));
    m_MenuCanvas->AddWidget(new Button(Vector2{200, 300}, "BACK", OnBackPressed));

    m_BackTexture = new Texture2D[widthCount * heightCount];
    for (size_t y = 0; y < heightCount; y++)
    {
        for (size_t x = 0; x < widthCount; x++)
        {
            m_BackTexture[y*widthCount+x] = LoadTexture(TextFormat("/cd/titlescreen/ts%01i%01i.png", y+1, x+1));
        }
    }
}

void SceneOptions::OnDectivated()
{
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