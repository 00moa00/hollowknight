#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"



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

	if (_Info.StateTime > 3.0f)
	{
		EventState_ = EventState::Battle;
		GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetInRoomMove);
	}

	//if (isRoarEnd_ == true)
	//{
	//	isRoarEnd_ = false;



	//	//GrimmAppearManager_.ChangeState("APPEAR_ROAR");

	//}
}

void Grimm::GrimmAppearRoarEnd(const StateInfo& _Info)
{
}

