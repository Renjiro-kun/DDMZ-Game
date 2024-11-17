#include <Scene/SceneBattle.h>

void SceneBattle::OnActivated()
{
    m_Camera.position = Vector3{1.f, 8.f, 1.f};
    m_Camera.target = (Vector3){0185.f, 0.4f, 0.f};
    m_Camera.up = Vector3{0.f, 1.f, 0.f};
    m_Camera.fovy = 45.f;
    m_Camera.projection = CAMERA_PERSPECTIVE;
    
    m_Skybox = LoadModel("/rd/skydome.obj");

    Texture2D skyTexture = LoadTexture("/rd/skydome.png");
    m_Skybox.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = skyTexture;
}

void SceneBattle::OnDectivated()
{

}

void SceneBattle::OnUpdate()
{

}

void SceneBattle::OnDraw3D()
{
    DrawModel(m_Skybox, Vector3{0.f, -6.f, 0.f}, 10.f, WHITE);
}

void SceneBattle::OnDraw2D()
{

}