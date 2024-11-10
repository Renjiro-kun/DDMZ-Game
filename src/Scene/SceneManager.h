#pragma once
#include <map>
#include <raylib/raylib.h>
#include "Scene.h"
#include "SceneMaze.h"

class SceneManager
{
public:
    static SceneManager& GetInstance()
    {
        static SceneManager instance;
        return instance;
    }
public:
    void Init();

    void Shutdown();

    void Update();

    void Draw3D();

    void Draw();

private:
    SceneManager() = default;
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

private:
    Scene* m_ActiveScene;
    std::map<int, Scene*> m_ScenesArray;
};