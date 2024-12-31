#pragma once
#include <Scene/Scene.h>

#include <Gameplay/FirstPersonCamera.h>
#include <Gameplay/Objects/Interactable.h>
#include <Helpers/EnvironmentController.h>
#include <Helpers/MazeGenerator.h>
#include <Sound/BgmManager.h>
#include <UI/HUD/MazeHUD.h>
#include <UI/Menu/PauseMenu.h>

#include <vector>
#include <array>
#include <memory>

class Canvas;
class InteractableInfo;

class SceneMaze : public Scene
{
public:
    void OnActivated();
    void OnDectivated();
    void OnUpdate();
    void OnDraw3D();
    void OnDraw2D();
    
    Color GetSceneBackgroundColor() { return m_MazeColor; }

    Camera& GetCamera() { return m_FpsCamera.GetCamera(); }
private:
    void LoadObjects();

    void CheckCollisions();

    void OnExitReached();

    void TriggerInteractable();

    void OnTimerElapsed();
private:
    const std::array<std::string, 3> m_LevelNames
    {
        "/rd/map01.ddmz",
        "/rd/map02.ddmz",
        "/rd/map03.ddmz"
    };
    // TODO: Modify to interactable objects
    std::vector<std::unique_ptr<Interactable>> m_MapObjects;

    MazeRuntimeInfo m_MapInfo;
    BGM_Handle m_BGM;
    Texture2D m_CubeAtlas;
    Model m_MazeModel;
    Vector3 m_OldCamPosition;
    Vector3 m_MapPosition;
    PauseMenu* m_PauseMenu;
    InteractableInfo* m_InteractableStates;
    InteractableContext m_InteractionContext;
    EnvironmentController m_EnvironmentController;

    MazeHUD m_HUD;
    Color m_MazeColor = RAYWHITE;

    FirstPersonCamera m_FpsCamera;
    bool m_CanInteract = false;
    int m_CurrentInteractableX = -1;
    int m_CurrentInteractableY = -1;
};