#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"



void Grimm::GrimmAppearWaitStart(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x > 5000)
	{
		KnightData::GetInst()->SetisBossBattle(true);
		GrimmAppearManager_.ChangeState("APPEAR_TELETPORT");

	}

}

void Grimm::GrimmAppearWaitEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearTeleportStart(const StateInfo& _Info)
{

	BossRoomGate_ = GetLevel()->CreateActor<BossRoomGate>();
	BossRoomGate_->GetTransform().SetWorldPosition({ 3643, -925 });


	GrimmBeam_ = GetLevel()->CreateActor<GrimmBeam>();
	GrimmBeam_->SetParent(this);
	GrimmBeam_->GetTransform().SetWorldMove({ 50,680, static_cast<float>(Z_ORDER::Object) });
	GrimmBeam_->GetTransform().SetWorldRotation({ 0,0,-7 });


	GrimmSpotLight_ = GetLevel()->CreateActor<GrimmSpotLight>();
	GrimmSpotLight_->GetTransform().SetWorldMove({ 0,-40, -100 });
	GrimmSpotLight_->SetParent(this);





	GetRenderer()->On();
	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

}

void Grimm::GrimmAppearTeleportUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isTeleportAppearEnd_ == true)
	{
		isTeleportAppearEnd_ = false;
		GrimmAppearManager_.ChangeState("APPEAR_IDLE1");

	}
}

void Grimm::GrimmAppearTeleportEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearIdle1Start(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

}

void Grimm::GrimmAppearIdle1Update(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 2.5f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_PILLAR");
	}
}

void Grimm::GrimmAppearIdle1End(const StateInfo& _Info)
{
}



void Grimm::GrimmAppearPillarStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("PILLAR_ANIMATION");
	FadePink* FadePink_ = GetLevel()->CreateActor<FadePink>();
	FadePink_->GetTransform().SetWorldPosition({ 5000, -GameEngineWindow::GetInst()->GetScale().hy(), -200 });


	GetRenderer()->ScaleToCutTexture(0);

}

void Grimm::GrimmAppearPillarUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isPillarEnd_ == true)
	{
		isPillarEnd_ = false;
		GrimmAppearManager_.ChangeState("APPEAR_PILLAR_LOOP");

	}
}

void Grimm::GrimmAppearPillarEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmAppearPillarLoopStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("PILLAR_LOOP_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

}

void Grimm::GrimmAppearPillarLoopUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 2.5f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_IDLE2");
	}
}

void Grimm::GrimmAppearPillarLoopEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearIdle2Start(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

}

void Grimm::GrimmAppearIdle2Update(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 1.5f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_CHANGE_MAP");
	}
}

void Grimm::GrimmAppearIdle2End(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearChangeMapStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMasterMap()->ChangeGrimmMap();
	FadePink* FadePink_ = GetLevel()->CreateActor<FadePink>();
	FadePink_->GetTransform().SetWorldPosition({ 5000, -GameEngineWindow::GetInst()->GetScale().hy(), -200 });

	GrimmBeam_->Death();
	GrimmSpotLight_->Death();

	GetLevel<GrimmLevel>()->GetGrimmCrowds()->On();

	ReSetAccTime();
}


void Grimm::GrimmAppearChangeMapUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 2.0f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_BOW");
	}
}

void Grimm::GrimmAppearChangeMapEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmAppearBowStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("BOW_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmAppearBowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isBowEnd_ == true)
	{
		isBowEnd_ = false;
		GrimmAppearManager_.ChangeState("APPEAR_ROAR");

	}
}

void Grimm::GrimmAppearBowEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmAppearRoarStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("ROAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
	BossRoarEffect* BossRoarEffect_ = GetLevel()->CreateActor<BossRoarEffect>();
	BossRoarEffect_->SetParent(this);
	BossRoarEffect_->GetTransform().SetLocalPosition({ -100, 250 });
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->SetRoomCamera(float4(3000, 1080), float4(5000, -923));
}

void Grimm::GrimmAppearRoarUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (_Info.StateTime > 2.0f)
	{
		EventState_ = EventState::Battle;
		GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_DISAPPEAR");
		SetChangeStateString(PatternType::BATTLE_BALLOON_START);

		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetInRoomMove);
	}
}

void Grimm::GrimmAppearRoarEnd(const StateInfo& _Info)
{
}

