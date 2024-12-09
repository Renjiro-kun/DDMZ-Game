#pragma once
#include <Scene/Scene.h>
#include <FirstPersonCamera.h>
#include <Sound/BgmManager.h>
#include <MazeGenerator.h>

#include <vector>
#include <array>

class SavePoint;

class SceneMaze : public Scene
{
public:
    void OnActivated();
    void OnDectivated();
    void OnUpdate();
    void OnDraw3D();
    void OnDraw2D();
    
    Camera& GetCamera() { return m_FpsCamera.GetCamera(); }
private:
    void LoadObjects();

    void CheckCollisions();
    void CalculateLight();

    void OnExitReached();
private:

    std::array<std::string, 2> m_LevelNames
    {
        "/rd/testMap.ddmz",
        "/rd/bigTileTest.ddmz"
    };
    // TODO: Modify to interactable objects
    std::vector<SavePoint*> m_MapObjects;

    MazeRuntimeInfo m_MapInfo;
    BGM_Handle m_BGM;
    Texture2D m_CubeAtlas;
    Model m_MazeModel;
    Vector3 m_OldCamPosition;
    Vector3 m_MapPosition;

    FirstPersonCamera m_FpsCamera;
    bool CanSave = false;
};