#include <Gameplay/TurnBased/BattleController.h>
#include <Gameplay/TurnBased/Actor.h>

void BattleController::AddActor(Actor* actor)
{
    m_Actors.push_back(actor);
}

void BattleController::OnUpdate()
{
    TurnContext ctx;
    ActionResult result = m_Actors[m_CurrentActor]->ProcessTurn(ctx);
    if(result != ActionResult::Processing)
    {
        switch (result)
        {
        case ActionResult::Attack:
            m_Actors[ctx.targetId]->TakeDamage(m_Actors[m_CurrentActor]->GetAttackValue());
            break;
        case ActionResult::Defend:
            m_Actors[m_CurrentActor]->Defend();
            break;
        case ActionResult::Item:
            //m_Actors[ctx.targetId]
            break;
        case ActionResult::Special:
            m_Actors[ctx.targetId]->TakeSpecialDamage(m_Actors[m_CurrentActor]->GetTypeAttackValue());
            break;
        default:
            break;
        }

        m_CurrentActor++;
        if(m_CurrentActor > m_Actors.size() - 1) m_CurrentActor = 0;
    }
}
