#include <pch.h>
#include <Scene/ScenesImpl/SceneMaze.h>
#include <Scene/SceneManager.h>
#include <Gameplay/Objects/SavePoint.h>


#include <VMU/SaveManager.h>

void SceneMaze::OnActivated()
{
    m_FpsCamera = FirstPersonCamera();

    Mesh mesh {0};
    int16_t levelIdx = SaveGameManager::GetInstance().GetCurrentLevel();

    MazeGenerator::GenerateMazeMap(m_LevelNames[levelIdx], mesh, m_MapInfo);
    m_MazeModel = LoadModelFromMesh(mesh);

    m_MazeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_MapInfo.atlas;

    m_MapPosition = { 0.f, 0.0f, 0.0f };          // Set model position
    LoadObjects();

    m_BGM = BGMManager::GetInstance().LoadSound("/cd/music/bgm_field.adpcm");
    BGMManager::GetInstance().Play(m_BGM);
    
    Vector2 spawnPosition {0.f, 0.f};
    for (auto& obj : m_MapInfo.objects)
    {
        if(obj.type == ObjectType::PlayerStart)
        {
            spawnPosition = obj.position;
        }
    }

    m_FpsCamera.SetPosition(Vector3{spawnPosition.x, 0.4f, spawnPosition.y});
}

void SceneMaze::OnDectivated()
{
    BGMManager::GetInstance().Stop(m_BGM);
    BGMManager::GetInstance().UnloadBGM(m_BGM);

    for (size_t i = 0; i < m_MapObjects.size(); i++)
    {
        delete m_MapObjects[i];
    }
    
    m_MapObjects.clear();
    m_MapInfo.objects.clear();
    m_MapInfo.collisionMask.clear();
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
    
    CanSave = false;
    // TODO: Add better interaction check
    if(collisionMask[playerCellY*m_MapInfo.width+playerCellX+1] == static_cast<char>(CollisionType::Object))
    {
        CanSave = true;
    }
}

void SceneMaze::OnUpdate()
{
    m_OldCamPosition = m_FpsCamera.GetPosition();
    m_FpsCamera.UpdateCamera(GetFrameTime());
    if(IsGamepadAvailable(0))
    {
        if(IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT) && CanSave)
        {
            SaveGameManager::GetInstance().SaveData();
        }
    }
    CheckCollisions();
}

void SceneMaze::OnDraw3D()
{
    DrawModel(m_MazeModel, m_MapPosition, 1.f, WHITE);
    for (size_t i = 0; i < m_MapObjects.size(); i++)
    {
        m_MapObjects[i]->OnDraw3D();
    }
    
}

void  SceneMaze::LoadObjects()
{
    for (size_t i = 0; i < m_MapInfo.objects.size(); i++)
    {
        if(m_MapInfo.objects[i].type == ObjectType::SavePoint)
        {
            RuntimeObjectInfo& obj = m_MapInfo.objects[i];
            m_MapObjects.emplace_back(new SavePoint(Vector3{obj.position.x, 0.0f, obj.position.y}));
        }
    }
    
}

void SceneMaze::OnDraw2D()
{

}

void SceneMaze::OnExitReached()
{
    int16_t lvlIdx = SaveGameManager::GetInstance().GetCurrentLevel();
    SceneId nextScene = SceneId::SCENE_MAZE;
    lvlIdx += 1;

    if(lvlIdx > m_LevelNames.size() - 1)
    {
        lvlIdx = 0;
        nextScene = SceneId::SCENE_TITLE_SCREEN;
    }

    SaveGameManager::GetInstance().SetCurrentLevel(lvlIdx);
    SaveGameManager::GetInstance().SaveData();

    SceneManager::GetInstance().LoadScene(nextScene);
}

void SceneMaze::CalculateLight()
{
    Color tint = MAGENTA;
    for (unsigned int i = 0; i < m_MazeModel.meshes[0].vertexCount; i++)
    {
        m_MazeModel.meshes[0].colors[i*4] = tint.r;
        m_MazeModel.meshes[0].colors[i*4+1] = tint.g;
        m_MazeModel.meshes[0].colors[i*4+2] = tint.b;
        m_MazeModel.meshes[0].colors[i*4+3] = tint.a;
    }
}