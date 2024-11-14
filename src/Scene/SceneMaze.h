#pragma once
#include "Scene.h"
#include "../FirstPersonCamera.h"

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
    void CalculateLight();
private:
    Texture2D m_CubicMap;
    Texture2D m_CubeAtlas;
    Model m_MazeModel;
    Color* m_MapPixels;
    Vector3 m_MapPosition;

    FirstPersonCamera m_FpsCamera;
};