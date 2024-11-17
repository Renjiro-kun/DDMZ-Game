#include <pch.h>
#include <Scene/SceneMaze.h>
#include <MazeGenerator.h>

void SceneMaze::OnActivated()
{
    m_FpsCamera = FirstPersonCamera();
    Image img = LoadImage("/rd/cubicmap.png");
    m_CubicMap = LoadTextureFromImage(img);

    Mesh mesh {0};
    MazeGenerator::GenerateMazeMap("/rd/testMap.ddmz", mesh);
    m_MazeModel = LoadModelFromMesh(mesh);

    m_CubeAtlas = LoadTexture("/rd/cubicmap_atlas.png");
    m_MazeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = m_CubeAtlas;

    m_MapPixels = LoadImageColors(img);

    m_MapPosition = { 0, 0.0f, 0.0f };          // Set model position

    m_BGM = BGMManager::GetInstance().LoadSound("/rd/bgm_field.adpcm");
    BGMManager::GetInstance().Play(m_BGM);
    UnloadImage(img);
}

void SceneMaze::OnDectivated()
{
    BGMManager::GetInstance().Stop(m_BGM);
    BGMManager::GetInstance().UnloadBGM(m_BGM);

    UnloadImageColors(m_MapPixels);

    UnloadTexture(m_CubicMap);
    UnloadTexture(m_CubeAtlas);
    UnloadModel(m_MazeModel);
}

void SceneMaze::OnUpdate()
{
    m_FpsCamera.UpdateCamera(GetFrameTime());
}

void SceneMaze::OnDraw3D()
{
    DrawModel(m_MazeModel, m_MapPosition, 1.f, WHITE);
}

void SceneMaze::OnDraw2D()
{
    DrawTextureEx(m_CubicMap, Vector2{640 - m_CubicMap.width*4.f - 20.f, 20.f}, 0.f, 1.f, WHITE);
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