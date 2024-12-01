#include <Scene/Scene.h>
#include <Gameplay/TurnBased/BattleController.h>
#include <raylib/raylib.h>

class SceneBattle : public Scene
{
public:
    void OnActivated();
    void OnDectivated();
    void OnUpdate();
    void OnDraw3D();
    void OnDraw2D();
    
    Camera& GetCamera() { return m_Camera; }

    Color GetSceneBackgroundColor() { return BLACK; }
private:
    BattleController m_BattleController;
    Model m_Skybox;
    Camera m_Camera;
};
