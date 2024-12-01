#pragma once
#include <Gameplay/TurnBased/Actor.h>

#include <UI/Canvas.h>

class PlayerActor : public Actor
{
public:
    ActionResult ProcessTurn(TurnContext& context) override;
private:
    Canvas m_ActionsCanvas;
};
