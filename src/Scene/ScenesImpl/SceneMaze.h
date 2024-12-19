#pragma once
#include <Scene/Scene.h>
#include <FirstPersonCamera.h>
#include <Sound/BgmManager.h>
#include <MazeGenerator.h>
#include <UI/Menu/PauseMenu.h>
#include <Gameplay/Objects/Interactable.h>
#include <UI/HUD/MazeHUD.h>
#include <EnvironmentController.h>

#include <vector>
#include <array>

class Canvas;

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

    void OnExitReached();

    void TriggerInteractable();
private:

    std::array<std::string, 2> m_LevelNames
    {
        "/rd/testMap.ddmz",
        "/rd/bigTileTest.ddmz"
    };
    // TODO: Modify to interactable objects
    std::vector<Interactable*> m_MapObjects;

    MazeRuntimeInfo m_MapInfo;
    BGM_Handle m_BGM;
    Texture2D m_CubeAtlas;
    Model m_MazeModel;
    Vector3 m_OldCamPosition;
    Vector3 m_MapPosition;
    PauseMenu* m_PauseMenu;
    InteractableContext m_InteractionContext;
    EnvironmentController m_EnvironmentController;

    MazeHUD m_HUD;

    FirstPersonCamera m_FpsCamera;
    bool m_CanInteract = false;
    int m_CurrentInteractableX = -1;
    int m_CurrentInteractableY = -1;
};