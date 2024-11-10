#include "SceneManager.h"

void SceneManager::Init()
{
    m_ScenesArray = std::map<int, Scene*>();
    m_ScenesArray.emplace(std::pair<int, Scene*>(0, new SceneMaze()));
    m_ActiveScene = m_ScenesArray.at(0);
    m_ActiveScene->OnActivated();
}

void SceneManager::Shutdown()
{
    for (auto it : m_ScenesArray)
    {
        delete it.second;
    }
    delete m_ActiveScene;
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