#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"

Grimm::Grimm() 
	:
	isTeleportAppearEnd_(false),
	isTeleportDiappearEnd_(false),
	isPillarEnd_(false),
	isBowEnd_(false),
	isRoarEnd_(false),


	EventState_(EventState::MAX),

	GrimmBeam_(nullptr),
	GrimmSpotLight_(nullptr)
{
}

Grimm::~Grimm() 
{
}

void Grimm::Start()
{
	SetName("Grimm");

	CreateCollisionComponent(float4{ 150, 200, 1 }, static_cast<int>(COLLISION_ORDER::Monster));
	//GetCollision()->GetTransform().SetWorldPosition({ 0, 50, 0 });
	//CreateWallCollisionComponent(float4{ 20, 20, 1 });


	CreateRendererComponent(float4{ 309, 508, 1 }, "Grimm Cln_Grimm_idle_right0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	GetRenderer()->ScaleToCutTexture(0);

	GetTransform().SetLocalPosition({ 300,-500, static_cast<float>(Z_ORDER::Monster) });
	SetHP(50);

	SetMoveDirection(float4::RIGHT);
	//SetDirRendererXScale();

	//================================
	//    Create Animation
	//================================



	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_idle0000-Sheet.png", 0, 11, 0.100f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("TELEPORT_APPEAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_teleport0000-Sheet.png", 0, 6, 0.100f, true));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 6; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		GetRenderer()->CreateFrameAnimationCutTexture("TELEPORT_DISAPPEAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_teleport0000-Sheet.png", BackAni, 0.070f, false));
	}

	GetRenderer()->CreateFrameAnimationCutTexture("PILLAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_flame_pillar0000-Sheet.png", 0, 14, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("PILLAR_LOOP_ANIMATION", FrameAnimation_DESC("Grimm Cln_grimm_boss_flame_pillar_talk_loop0000-Sheet.png", 0, 3, 0.050f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("BOW_ANIMATION", FrameAnimation_DESC("Grimm NPC_Grimm_bow0000-Sheet.png", 0, 6, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("ROAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_roar0000-Sheet.png", 0, 3, 0.050f, false));



	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");


	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("TELEPORT_APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTeleportAppearEnd_ = true;

		});


	GetRenderer()->AnimationBindEnd("TELEPORT_DISAPPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTeleportDiappearEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("BOW_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isBowEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("PILLAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isPillarEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("ROAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isRoarEnd_ = true;

		});

	//================================
	//    Create State | Appear
	//================================
	GrimmAppearManager_.CreateStateMember("WAIT"
		, std::bind(&Grimm::GrimmAppearWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearWaitStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearWaitEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_TELETPORT"
		, std::bind(&Grimm::GrimmAppearTeleportUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearTeleportStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearTeleportEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_IDLE1"
		, std::bind(&Grimm::GrimmAppearIdle1Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearIdle1Start, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearIdle1End, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_PILLAR"
		, std::bind(&Grimm::GrimmAppearPillarUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearPillarStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearPillarEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_PILLAR_LOOP"
		, std::bind(&Grimm::GrimmAppearPillarLoopUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearPillarLoopStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearPillarLoopEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_IDLE2"
		, std::bind(&Grimm::GrimmAppearIdle2Update, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearIdle2Start, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearIdle2End, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_CHANGE_MAP"
		, std::bind(&Grimm::GrimmAppearChangeMapUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearChangeMapStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearChangeMapEnd, this, std::placeholders::_1));


	GrimmAppearManager_.CreateStateMember("APPEAR_BOW"
		, std::bind(&Grimm::GrimmAppearBowUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearBowStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearBowEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("APPEAR_ROAR"
		, std::bind(&Grimm::GrimmAppearRoarUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmAppearRoarStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmAppearRoarEnd, this, std::placeholders::_1));

	GrimmAppearManager_.ChangeState("WAIT");

	EventState_ = EventState::Appear;
	GetRenderer()->Off();
}

void Grimm::Update(float _DeltaTime)
{
	switch (EventState_)
	{
	case EventState::Appear:
		GrimmAppearManager_.Update(_DeltaTime);
		break;
	case EventState::Battle:
		break;
	case EventState::Talking:
		break;
	case EventState::MAX:
		break;
	default:
		break;
	}
}

void Grimm::SetMonsterHit(int _Damage, float4 _StunDir)
{
}

void Grimm::GrimmAppearWaitStart(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().x > 5000)
	{
		GrimmAppearManager_.ChangeState("APPEAR_TELETPORT");

	}
	
}

void Grimm::GrimmAppearWaitEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmAppearTeleportStart(const StateInfo& _Info)
{
	GrimmBeam_ = GetLevel()->CreateActor<GrimmBeam>();
	GrimmBeam_->SetParent(this);
	GrimmBeam_->GetTransform().SetWorldMove({ 50,680, static_cast<float>(Z_ORDER::Object)});
	GrimmBeam_->GetTransform().SetWorldRotation({0,0,-7});


	GrimmSpotLight_ = GetLevel()->CreateActor<GrimmSpotLight>();
	GrimmSpotLight_->GetTransform().SetWorldMove({ 0,5, -100 });
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
	FadePink_->GetTransform().SetWorldPosition({5000, -GameEngineWindow::GetInst()->GetScale().hy(), -200});


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
	BossRoarEffect_->GetTransform().SetLocalPosition({ 0, 130 });
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossShaking);

}

void Grimm::GrimmAppearRoarUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isRoarEnd_ == true)
	{
		isRoarEnd_ = false;
		//GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetMove);


		//GrimmAppearManager_.ChangeState("APPEAR_ROAR");

	}
}

void Grimm::GrimmAppearRoarEnd(const StateInfo& _Info)
{
}

