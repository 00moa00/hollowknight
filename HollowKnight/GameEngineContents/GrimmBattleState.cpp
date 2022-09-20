#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"



void Grimm::GrimmBattleTeleportAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");







}

void Grimm::GrimmBattleTeleportAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isTeleportAppearEnd_ == true)
	{
		isTeleportAppearEnd_ = false;
		GrimmBattleManager_.ChangeState(ChangeState_);
		return;

	}
}

void Grimm::GrimmBattleTeleportAppearEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleTeleportDisappearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_DISAPPEAR_ANIMATION");

}

void Grimm::GrimmBattleTeleportDisappearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isTeleportDiappearEnd_ == true)
	{
		isTeleportDiappearEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_APPEAR");
		return;

	}


}
void Grimm::GrimmBattleTeleportDisappearEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonStartStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleBalloonStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStartStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStartEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashEndtStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashEndtUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashEndtEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleSlashStartStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashStartEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashUpStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashUpEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleFireStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleFireUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleFireEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeStartStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleSpikeStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastStartStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlCastStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlStunStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlStunBatStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunBatUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunBatEnd(const StateInfo& _Info)
{
}
