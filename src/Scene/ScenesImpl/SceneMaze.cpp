#include <Defines.h>
#include <Scene/ScenesImpl/SceneMaze.h>
#include <Scene/SceneManager.h>
#include <Gameplay/Objects/SavePoint.h>
#include <Gameplay/Objects/ItemChest.h>
#include <Gameplay/Objects/Door.h>
#include <Gameplay/Objects/ObjectRepository.h>
#include <Gameplay/TimerController.h>
#include <Input/InputContextManager.h>

#include <VMU/SaveManager.h>

void OnExitPressed();

void SceneMaze::OnActivated()
{
    Mesh mesh {0};
    int16_t levelIdx = SaveGameManager::GetInstance().GetCurrentLevel();

    MazeGenerator::GenerateMazeMap(m_LevelNames[levelIdx], mesh, m_MapInfo);
    m_MazeModel = LoadModelFromMesh(mesh);

    m_MazeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_MapInfo.atlas;

    m_MapPosition = { 0.f, 0.0f, 0.0f };          // Set model position
    m_InteractableStates = SaveGameManager::GetInstance().GetInteractableStates();
    LoadObjects();

    m_HUD.OnActivate();

    m_BGM = BGMManager::GetInstance().LoadSound(GET_ASSET_FROM_CD("music/bgm_field.adpcm"));
    BGMManager::GetInstance().Play(m_BGM);
    
    m_PauseMenu = new PauseMenu();

    int posX = SaveGameManager::GetInstance().GetPlayerPositionX();
    int posY = SaveGameManager::GetInstance().GetPlayerPositionY();

    Vector2 spawnPosition {posX, posY};
    if(posX == 0 && posY == 0)
    {
        for (auto& obj : m_MapInfo.objects)
        {
            if(obj.type == ObjectType::PlayerStart)
            {
                spawnPosition = obj.position;
            }
        }
    }
    
    m_FpsCamera.OnActivate();
    m_FpsCamera.SetPosition(Vector3{spawnPosition.x, 0.4f, spawnPosition.y});
    ObjectRepository::GetInstance().OnActivate();
    m_MazeColor = m_MapInfo.BackColor;
    m_EnvironmentController.OnActivate();
    m_EnvironmentController.SetLightColor(m_MapInfo.LightColor);
    m_EnvironmentController.SetFogColor(m_MapInfo.FogColor);
    m_EnvironmentController.SetFogDepth(m_MapInfo.FogDepth);
    m_FpsCamera.SetCullingDistance(m_MapInfo.FogDepth);

    float timeLimit = SaveGameManager::GetInstance().GetTimeLimit();
    if(timeLimit <= 0.f)
    {
        timeLimit = m_MapInfo.TimeLimit;
    }

    TimerController::GetInstance().StartTimer(timeLimit);
}

void SceneMaze::OnDectivated()
{
    TimerController::GetInstance().StopTimer();
    m_HUD.OnDeactivate();
    m_EnvironmentController.OnDeactivate();
    ObjectRepository::GetInstance().OnDeactivate();
    BGMManager::GetInstance().Stop(m_BGM);
    BGMManager::GetInstance().UnloadBGM(m_BGM);
    
    for (size_t i = 0; i < m_MapObjects.size(); i++)
    {
        m_MapObjects[i]->Unload();
    }
    
    delete m_PauseMenu;

    m_MapObjects.clear();
    m_MapInfo.objects.clear();
    m_MapInfo.collisionMask.clear();
    m_FpsCamera.OnDeactivate();
    UnloadTexture(m_CubeAtlas);
    UnloadModel(m_MazeModel);
}

void SceneMaze::CheckCollisions()
{
    Vector2 playerPos = { m_FpsCamera.GetPosition().x, m_FpsCamera.GetPosition().z };
    float playerRadius = 0.1f;

    int playerCellX = (int)(playerPos.x - m_MapPosition.x + 0.5f);
    int playerCellY = (int)(playerPos.y - m_MapPosition.z + 0.5f);

    if(playerCellX < 0) playerCellX = 0;
    else if(playerCellX > m_MapInfo.width) playerCellX = m_MapInfo.width - 1;

    if(playerCellY < 0) playerCellY = 0;
    else if(playerCellY > m_MapInfo.height) playerCellY = m_MapInfo.height - 1;

    // TODO: Check only close cells
    std::vector<char>& collisionMask = m_MapInfo.collisionMask;
    for (size_t y = 0; y < m_MapInfo.height; y++)
    {
        for (size_t x = 0; x < m_MapInfo.width; x++)
        {
            if((collisionMask[y*m_MapInfo.width+x] == static_cast<char>(CollisionType::Wall) ||
                collisionMask[y*m_MapInfo.width+x] == static_cast<char>(CollisionType::Object)) &&
                (CheckCollisionCircleRec(playerPos, playerRadius, 
                Rectangle{m_MapPosition.x - 0.5f + x *1.f, m_MapPosition.z - 0.5f + y * 1.f, 1.f, 1.f})))
            {
                m_FpsCamera.SetPosition(m_OldCamPosition);
            }   
            if(collisionMask[y*m_MapInfo.width+x] == static_cast<char>(CollisionType::Exit) &&
                (CheckCollisionCircleRec(playerPos, playerRadius, 
                Rectangle{m_MapPosition.x - 0.5f + x *1.f, m_MapPosition.z - 0.5f + y * 1.f, 1.f, 1.f})))
            {
                OnExitReached();
            }
        }
    }
    
    m_CanInteract = false;
    m_CurrentInteractableX = -1;
    m_CurrentInteractableY = -1;

    // Check interactable objects
    Vector3 camForward = m_FpsCamera.GetForwardVector();
    int xOffset = (int)roundf(camForward.x);
    int yOfsset = (int)roundf(camForward.z);
    if(collisionMask[(playerCellY+yOfsset)*m_MapInfo.width+playerCellX+xOffset] == static_cast<char>(CollisionType::Object))
    {
        m_CanInteract = true;
        m_CurrentInteractableX = playerCellX + xOffset;
        m_CurrentInteractableY = playerCellY + yOfsset;
    }
}

void SceneMaze::OnUpdate()
{
    if(TimerController::GetInstance().IsElapsed())
    {
        OnTimerElapsed();
    }
    m_OldCamPosition = m_FpsCamera.GetPosition();
    m_FpsCamera.UpdateCamera(GetFrameTime());
    InputContext currentContext = InputContextManager::GetInstance().CurrentInputComtext();
    if(IsGamepadAvailable(0) && currentContext == InputContext::Default)
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && m_CanInteract)
        {
            TriggerInteractable();
        }
    }
    m_PauseMenu->OnUpdate();
    CheckCollisions();
    m_HUD.SetInteractActive(m_CanInteract);
}

void SceneMaze::TriggerInteractable()
{
    Vector2 playerPos = { m_FpsCamera.GetPosition().x, m_FpsCamera.GetPosition().z };
    int playerCellX = (int)(playerPos.x - m_MapPosition.x + 0.5f);
    int playerCellY = (int)(playerPos.y - m_MapPosition.z + 0.5f);

    int interactIdx = -1;
    for (size_t i = 0; i < m_MapObjects.size(); i++)
    {
        if(m_MapObjects[i]->IsOnCell(m_CurrentInteractableX, m_CurrentInteractableY))
        {
            interactIdx = i;
            break;
        }
    }

    if(interactIdx > -1 && interactIdx < m_MapObjects.size())
    {
        m_InteractionContext.levelIdx = SaveGameManager::GetInstance().GetCurrentLevel();
        m_InteractionContext.playerPosX = playerCellX;
        m_InteractionContext.playerPosY = playerCellY;
        m_InteractionContext.currentTimeLimit = TimerController::GetInstance().GetCurrentTime();
        InteractableInfo* currentInteractableState = nullptr;
        for (size_t i = 0; i < INTERACTABLE_STATES_SIZE; i++)
        {
            Vector3 pos = m_MapObjects[interactIdx]->GetPosition();
            if(m_InteractableStates[i].CheckObject(pos.x, pos.z))
            {
                currentInteractableState = &m_InteractableStates[i];
                break;
            }
        }
        m_InteractionContext.currentInteractableState = currentInteractableState;
        m_MapObjects[interactIdx]->SetContext(&m_InteractionContext);
        m_MapObjects[interactIdx]->Interact();
    }
}

void SceneMaze::OnDraw3D()
{
    m_EnvironmentController.Enable();
    DrawModel(m_MazeModel, m_MapPosition, 1.f, WHITE);
    for (size_t i = 0; i < m_MapObjects.size(); i++)
    {
        if(m_FpsCamera.IsInDrawingRange(m_MapObjects[i]->GetPosition()))
        {
            m_MapObjects[i]->OnDraw3D();
        }
    }
    m_EnvironmentController.Disable();
}

void SceneMaze::OnTimerElapsed()
{
    SceneManager::GetInstance().LoadScene(SceneId::SCENE_GAMEOVER);
}

void  SceneMaze::LoadObjects()
{
    bool saveAvailable = m_InteractableStates[0].IsValidObject();
    size_t currentStateIdx = 0;
    for (size_t i = 0; i < m_MapInfo.objects.size(); i++)
    {
        bool state = false;
        RuntimeObjectInfo& obj = m_MapInfo.objects[i];
        if(m_MapInfo.objects[i].type == ObjectType::SavePoint)
        {
            m_MapObjects.push_back(std::make_unique<SavePoint>(Vector3{obj.position.x, 0.0f, obj.position.y}, obj.orientation));
        }
        else if(m_MapInfo.objects[i].type == ObjectType::ItemChest)
        {
            m_MapObjects.push_back(std::make_unique<ItemChest>(Vector3{obj.position.x, 0.0f, obj.position.y}, obj.orientation, obj.itemId));
        }
        else if(m_MapInfo.objects[i].type == ObjectType::Door)
        {
            m_MapObjects.push_back(std::make_unique<Door>(Vector3{obj.position.x, 0.0f, obj.position.y}, 
                                                            obj.itemId, obj.orientation, m_MapInfo.width, &m_MapInfo.collisionMask));
        }
        else
        {
            continue;
        }
        if(saveAvailable)
        {
            for (size_t i = 0; i < INTERACTABLE_STATES_SIZE; i++)
            {
                if(m_InteractableStates[i].CheckObject(obj.position.x, obj.position.y))
                {
                    state = m_InteractableStates[i].State;
                    break;
                }
            }

            auto& mapObject = m_MapObjects.at(m_MapObjects.size() - 1);
            mapObject->SetState(state);
        }
        else
        {
            m_InteractableStates[currentStateIdx].CellX = obj.position.x;
            m_InteractableStates[currentStateIdx].CellY = obj.position.y;
            m_InteractableStates[currentStateIdx].State = false;
            currentStateIdx++;
        }
    }
}

void SceneMaze::OnDraw2D()
{
    m_PauseMenu->OnDraw2D();
    m_HUD.OnDraw2D();
    m_FpsCamera.OnDraw2D();
}

void SceneMaze::OnExitReached()
{
    int16_t lvlIdx = SaveGameManager::GetInstance().GetCurrentLevel();
    SceneId nextScene = SceneId::SCENE_MAZE;
    lvlIdx += 1;

    if(lvlIdx > m_LevelNames.size() - 1)
    {
        lvlIdx = 0;
        nextScene = SceneId::SCENE_CREDITS;
        SaveGameManager::GetInstance().ResetSaveGame();
    }

    SaveGameManager::GetInstance().SetPlayerPositionX(0);
    SaveGameManager::GetInstance().SetPlayerPositionY(0);
    SaveGameManager::GetInstance().SetTimeLimit(-1.f);
    m_PauseMenu->DisableCanvasHack();

    SaveGameManager::GetInstance().SetCurrentLevel(lvlIdx);
    SaveGameManager::GetInstance().ResetInteractableStates();
    SaveGameManager::GetInstance().SaveData();

    SceneManager::GetInstance().LoadScene(nextScene);
}