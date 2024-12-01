#pragma once
#include <vector>

enum class ActionResult : char
{
    Attack = 0,
    Defend = 1,
    Special = 2,
    Item = 3,
    Processing = 4
};

enum class ActorTeam : char
{
    Player = 0,
    Enemy = 1
};

class Actor;

struct TurnContext
{
    std::vector<Actor*> enemyActors;
    short targetId;
};

class Actor
{
public:
    Actor();
    ~Actor();
public:
    virtual ActionResult ProcessTurn(TurnContext& context);

    void TakeDamage(short damage);
    void Defend();
    void TakeSpecialDamage(short damage);


    short GetAttackValue() const {return m_Attack; }
    short GetTypeAttackValue() const { return m_TypeAttack; }
private:
    short m_Attack;
    short m_TypeAttack;
    short m_Defence;

    ActorTeam m_Team;    

    short m_Health;
    short m_SpecialPoints;
};