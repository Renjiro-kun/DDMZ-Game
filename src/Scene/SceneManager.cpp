#include <Scene/SceneManager.h>
#include <Scene/ScenesImpl/SceneMaze.h>
#include <Scene/ScenesImpl/SceneMainMenu.h>
#include <Scene/ScenesImpl/SceneBattle.h>
#include <Scene/ScenesImpl/SceneTitle.h>

void SceneManager::Init()
{
    m_ScenesArray = std::map<SceneId, Scene*>();
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SceneId::SCENE_MAZE, new SceneMaze()));
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SceneId::SCENE_MAIN_MENU, new SceneMainMenu()));
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SceneId::SCENE_BATTLE, new SceneBattle()));
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SceneId::SCENE_TITLE_SCREEN, new SceneTitle()));
}

void SceneManager::Shutdown()
{
    for (auto it : m_ScenesArray)
    {
        delete it.second;
    }
    delete m_ActiveScene;
}

void SceneManager::LoadScene(SceneId id)
{
    if(m_ActiveScene != nullptr)
    {
        m_ActiveScene->OnDectivated();
    }
    m_ActiveScene = m_ScenesArray.at(id);
    m_ActiveScene->OnActivated();
}

void SceneManager::Update()
{
    m_ActiveScene->OnUpdate();
}

void SceneManager::Draw3D()
{
    BeginMode3D(m_ActiveScene->GetCamera());
        m_ActiveScene->OnDraw3D();
    EndMode3D();
}

void SceneManager::ClearScreen()
{
    ClearBackground(m_ActiveScene->GetSceneBackgroundColor());
}

void SceneManager::Draw()
{
    m_ActiveScene->OnDraw2D();
}