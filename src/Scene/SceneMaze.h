#pragma once
#include <Scene/Scene.h>
#include <FirstPersonCamera.h>
#include <Sound/BgmManager.h>
#include <MazeGenerator.h>

#include <vector>

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
    void CheckCollisions();
    void CalculateLight();

    void OnExitReached();
private:
    MazeRuntimeInfo m_MapInfo;
    BGM_Handle m_BGM;
    Texture2D m_CubeAtlas;
    Model m_MazeModel;
    Vector3 m_OldCamPosition;
    Vector3 m_MapPosition;

    FirstPersonCamera m_FpsCamera;
};