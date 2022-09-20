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

	isCastEndEnd_(false),

	isSlashStartEnd_(false),
	isSlashEnd_(false),
	isSlashEndEnd_(false),

	isDashStartEnd_(false),
	isDashUpEnd_(false),

	isStunHitEnd_(false),



	EventState_(EventState::MAX),

	GrimmBeam_(nullptr),
	GrimmSpotLight_(nullptr),
	BossRoomGate_(nullptr)
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
	//    Create Animation | Common
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("TELEPORT_APPEAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_teleport0000-Sheet.png", 0, 6, 0.100f, true));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 6; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		GetRenderer()->CreateFrameAnimationCutTexture("TELEPORT_DISAPPEAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_teleport0000-Sheet.png", BackAni, 0.070f, false));
	}


	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_idle0000-Sheet.png", 0, 11, 0.100f, true));
	

	//================================
	//    Create Animation | Appear
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("PILLAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_flame_pillar0000-Sheet.png", 0, 14, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("PILLAR_LOOP_ANIMATION", FrameAnimation_DESC("Grimm Cln_grimm_boss_flame_pillar_talk_loop0000-Sheet.png", 0, 3, 0.050f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("BOW_ANIMATION", FrameAnimation_DESC("Grimm NPC_Grimm_bow0000-Sheet.png", 0, 6, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("ROAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_roar0000-Sheet.png", 0, 3, 0.050f, false));


	//================================
	//    Create Animation | Battle
	//================================
	GetRenderer()->CreateFrameAnimationCutTexture("BALLON_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_boss_balloon_attack0000-Sheet.png", 0, 1, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("BALLON_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_boss_balloon_attack0000-Sheet.png", 1, 4, 0.050f, true));

	
	
	GetRenderer()->CreateFrameAnimationCutTexture("CAST_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_cast0000-Sheet.png", 0, 7, 0.050f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 7; i > -1; --i)
		{
			BackAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("CAST_END_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_cast0000-Sheet.png", BackAni, 0.050f, false));
	}

	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 0, 4, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 5, 7, 0.050f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_END_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 8, 1, 0.050f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_slash_antic0000-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_SLASH_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_slash0000-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_UP_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_anims_v050000-Sheet.png", 0, 5, 0.050f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("STUN_HIT_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_stun_explode0000-Sheet.png", 0, 4, 0.050f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("SPRIKE_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_Boss_ground_spike_attack0003-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SPRIKE_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_Boss_ground_spike_attack0003-Sheet.png", 4, 6, 0.050f, true));



	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");


	//====================================
	//    Create Bind Animation | Commomn
	//====================================

	GetRenderer()->AnimationBindEnd("TELEPORT_APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTeleportAppearEnd_ = true;

		});


	GetRenderer()->AnimationBindEnd("TELEPORT_DISAPPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isTeleportDiappearEnd_ = true;

		});

	//======================================
	//    Create Bind Animation | Appear
	//======================================
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


	//======================================
	//    Create Bind Animation | Battle
	//======================================
	GetRenderer()->AnimationBindEnd("BALLON_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("BALLON_ANIMATION");

		});

	GetRenderer()->AnimationBindEnd("CAST_END_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isCastEndEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("AIR_DASH_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDashStartEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("AIR_DASH_END_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDashUpEnd_ = true;

		});


	GetRenderer()->AnimationBindEnd("SLASH_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashStartEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("SLASH_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("SLASH_UP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEndEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("STUN_HIT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isStunHitEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("SPRIKE_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("SPRIKE_ANIMATION");

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


	//================================
	//    Create State | Battle
	//================================

	GrimmAppearManager_.CreateStateMember("BATTLE_TELEPORT_APPEAR"
		, std::bind(&Grimm::GrimmBattleTeleportAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleTeleportAppearStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleTeleportAppearEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_TELEPORT_DISAPPEAR"
		, std::bind(&Grimm::GrimmBattleTeleportDisappearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleTeleportDisappearStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleTeleportDisappearEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_BALLOON"
		, std::bind(&Grimm::GrimmBattleBalloonUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleBalloonStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleBalloonEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_SLASH"
		, std::bind(&Grimm::GrimmBattleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSlashStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSlashEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_FIRE"
		, std::bind(&Grimm::GrimmBattleFireUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleFireStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleFireEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_SPIKE"
		, std::bind(&Grimm::GrimmBattleSpikeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSpikeStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSpikeEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_CAST"
		, std::bind(&Grimm::GrimmBattlCastUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlCastStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlCastEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_STUN"
		, std::bind(&Grimm::GrimmBattlStunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlStunStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlStunEnd, this, std::placeholders::_1));

	GrimmAppearManager_.CreateStateMember("BATTLE_STUN_BAT"
		, std::bind(&Grimm::GrimmBattlStunBatUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlStunBatStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlStunBatEnd, this, std::placeholders::_1));

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
	BossRoomGate_->GetTransform().SetWorldPosition({3643, -925});
	//BossRoomGate_-


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
