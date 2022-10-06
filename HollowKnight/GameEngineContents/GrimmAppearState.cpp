#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"

#include "GrimmFlamePillarEffect.h"

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
	BossRoomRightGate_ = GetLevel()->CreateActor<BossRoomGate>();
	BossRoomRightGate_->GetTransform().SetWorldPosition({ 6000, -925 });
	BossRoomRightGate_->GetTransform().PixLocalNegativeX();


	GrimmBeam_ = GetLevel()->CreateActor<GrimmBeam>();
	GrimmBeam_->SetParent(this);
	GrimmBeam_->GetTransform().SetWorldMove({ 50,680, static_cast<float>(Z_ORDER::Object) });
	GrimmBeam_->GetTransform().SetWorldRotation({ 0,0,-7 });


	GrimmSpotLight_ = GetLevel()->CreateActor<GrimmSpotLight>();
	GrimmSpotLight_->GetTransform().SetWorldMove({ 0,-40, -100 });
	GrimmSpotLight_->SetParent(this);

	GrimmSmoke_->SetSmokeOn();
	GrimmSmoke_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Effect) });


	GetRenderer()->On();
	GetRenderer()->ChangeFrameAnimation("TELEPORT_NONLOOP_APPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

	KnightSoundManager::GetInst()->BgmOff();
	GameEngineSoundPlayer Effect = GameEngineSound::SoundPlayControl("grimm_explode_into_bats.ogg");
	Effect.Volume(0.4f);
}

void Grimm::GrimmAppearTeleportUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.0f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_IDLE1");
	}
}

void Grimm::GrimmAppearTeleportEnd(const StateInfo& _Info)
{
	GetCollision()->Off();
}

void Grimm::GrimmAppearIdle1Start(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

	DialogueSet_->SetDialogueOn();
}

void Grimm::GrimmAppearIdle1Update(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 3.0f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_PILLAR");
	}
}

void Grimm::GrimmAppearIdle1End(const StateInfo& _Info)
{
	DialogueSet_->SetDialogueOff();
}

void Grimm::GrimmAppearPillarStart(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);
	GetRenderer()->ChangeFrameAnimation("PILLAR_ANIMATION");


	GetRenderer()->ScaleToCutTexture(0);

	GrimmFlamePillarEffect* GrimmFlamePillarEffect_ = GetLevel()->CreateActor<GrimmFlamePillarEffect>();
	GrimmFlamePillarEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Effect) });
	
	GameEngineSound::SoundPlayOneShot("grimm_cape_open_for_cast.ogg");

}

void Grimm::GrimmAppearPillarUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GetRenderer()->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() == 10)
	{
		if (StartPink_ == nullptr)
		{
			StartPink_ = GetLevel()->CreateActor<FadePink>();
			StartPink_->GetTransform().SetWorldPosition({ 5000, -GameEngineWindow::GetInst()->GetScale().hy(), -200 });
			GameEngineSound::SoundPlayOneShot("grimm_fireball_cast.ogg");

		}
	}

	if (isPillarEnd_ == true)
	{
		isPillarEnd_ = false;
		GrimmAppearManager_.ChangeState("APPEAR_PILLAR_LOOP");

	}
}

void Grimm::GrimmAppearPillarEnd(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);
}

void Grimm::GrimmAppearPillarLoopStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("PILLAR_LOOP_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	ReSetAccTime();

	WindSound_ = GameEngineSound::SoundPlayControl("grimm_balloon_shooting_fireballs_loop.ogg", 50);
	WindSound_.Volume(0.4f);
}

void Grimm::GrimmAppearPillarLoopUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 2.5f)
	{
		WindSound_.Stop();
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
		if (ArmRenderer_ != nullptr)
		{
			ArmRenderer_->On();
			ReSetAccTime();
		}
	}

	if (ArmRenderer_ == nullptr)
	{
		if (GetAccTime() > 1.0f)
		{
			GrimmAppearManager_.ChangeState("APPEAR_CHANGE_MAP");
		}

	}
}

void Grimm::GrimmAppearIdle2End(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearChangeMapStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("col_cage_open.ogg");
	GameEngineSound::SoundPlayOneShot("crowd_murmur_loop.ogg");

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
	if (GetAccTime() > 2.5f)
	{
		GrimmAppearManager_.ChangeState("APPEAR_BOW");
		return;
	}
}

void Grimm::GrimmAppearChangeMapEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearBowStart(const StateInfo& _Info)
{

	GetRenderer()->ChangeFrameAnimation("BOW_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	KnightSoundManager::GetInst()->BgmOn("S82-115 Grimm.ogg", 200);
}

void Grimm::GrimmAppearBowUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 1.0f)
	{
		isBowEnd_ = false;
		GrimmAppearManager_.ChangeState("APPEAR_ROAR");
	}
	if (isBowEnd_ == true)
	{


	}
}

void Grimm::GrimmAppearBowEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmAppearRoarStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("grimm_scream.ogg");


	GetRenderer()->ChangeFrameAnimation("ROAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
	BossRoarEffect* BossRoarEffect_ = GetLevel()->CreateActor<BossRoarEffect>();
	BossRoarEffect_->SetParent(this);
	BossRoarEffect_->GetTransform().SetLocalPosition({ -180.f, 250.f });
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

