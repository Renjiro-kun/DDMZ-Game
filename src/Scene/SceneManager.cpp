#include "SceneManager.h"
#include "SceneMaze.h"
#include "SceneMainMenu.h"

void SceneManager::Init()
{
    m_ScenesArray = std::map<SceneId, Scene*>();
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SCENE_MAZE, new SceneMaze()));
    m_ScenesArray.emplace(std::pair<SceneId, Scene*>(SCENE_MAIN_MENU, new SceneMainMenu()));
    //m_ActiveScene = m_ScenesArray.at(SceneId::SCENE_MAZE);
    //m_ActiveScene->OnActivated();
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

void SceneManager::Draw()
{
    m_ActiveScene->OnDraw2D();
}