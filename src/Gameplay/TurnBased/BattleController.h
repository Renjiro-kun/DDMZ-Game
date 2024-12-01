#pragma once
#include <vector>

class Actor;

class BattleController
{
public:
    BattleController(/* args */) = default;
    ~BattleController() = default;

    void AddActor(Actor* actor);

    void OnUpdate();

private:

private:
    std::vector<Actor*> m_Actors;
    short m_CurrentAct;

    short m_CurrentActor;
};