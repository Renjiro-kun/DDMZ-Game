#pragma once
#include <map>
#include <raylib/raylib.h>

class Scene;

enum SceneId : int
{
    SCENE_MAIN_MENU = 0,
    SCENE_MAZE = 1,
    SCENE_BATTLE = 2
};

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

    void LoadScene(SceneId id);

    void ClearScreen();

private:
    SceneManager() = default;
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

private:
    Scene* m_ActiveScene;
    std::map<SceneId, Scene*> m_ScenesArray;
};