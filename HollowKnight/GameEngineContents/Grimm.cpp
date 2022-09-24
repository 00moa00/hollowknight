#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"

#include "GrimmFire.h"

#include <GameEngineBase/GameEngineRandom.h>

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
	isBllonStartEnd_(false),
	isCastStartEnd_(false),
	isSprikeStartEnd_(false),

	MapCenterX_(0.0f),

	ChangeState_(""),
	PrevChangeState_(0),
	PatternRamdom_(0),
	BirdCreateTimer_(0.0f),

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
	MapCenterX_ = 4800.f;

	CreateCollisionComponent(float4{ 150, 200, 1 }, static_cast<int>(COLLISION_ORDER::Monster));
	//GetCollision()->GetTransform().SetWorldPosition({ 0, 50, 0 });
	CreateWallCollisionComponent(float4{ 20, 20, 1 });


	CreateRendererComponent(float4{ 309, 508, 1 }, "Grimm Cln_Grimm_idle_right0000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->GetTransform().SetLocalPosition({0,-50});
	GetTransform().SetLocalPosition({ 300,-500, static_cast<float>(Z_ORDER::Monster) });
	SetHP(50);

	SetMoveDirection(float4::RIGHT);
	//SetMonsterDirection();

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

	
	GetRenderer()->CreateFrameAnimationCutTexture("CASTS_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_cast0000-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("CAST_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_cast0000-Sheet.png", 0, 7, 0.050f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 7; i > -1; --i)
		{
			BackAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("CAST_END_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_cast0000-Sheet.png", BackAni, 0.050f, false));
	}

	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 0, 4, 0.030f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 5, 7, 0.050f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("AIR_DASH_END_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_air_dash0000-Sheet.png", 8, 15, 0.050f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_slash_antic0000-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_SLASH_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_slash0000-Sheet.png", 0, 3, 0.050f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_UP_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_anims_v050000-Sheet.png", 0, 5, 0.050f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("STUN_HIT_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_stun_explode0000-Sheet.png", 0, 4, 0.050f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("SPRIKE_START_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_Boss_ground_spike_attack0003-Sheet.png", 0, 6, 0.050f, false));
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
			isBllonStartEnd_ = true;

		});

	GetRenderer()->AnimationBindEnd("CASTS_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isCastStartEnd_ = true;
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
			isSprikeStartEnd_ = true;
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

	//================================
	//    Create State | Battle
	//================================

	GrimmBattleManager_.CreateStateMember("BATTLE_TELEPORT_APPEAR"
		, std::bind(&Grimm::GrimmBattleTeleportAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleTeleportAppearStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleTeleportAppearEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_TELEPORT_DISAPPEAR"
		, std::bind(&Grimm::GrimmBattleTeleportDisappearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleTeleportDisappearStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleTeleportDisappearEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_BALLOON_START"
		, std::bind(&Grimm::GrimmBattleBalloonStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleBalloonStartStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleBalloonStartEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_BALLOON"
		, std::bind(&Grimm::GrimmBattleBalloonUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleBalloonStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleBalloonEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_SLASH_START"
		, std::bind(&Grimm::GrimmBattleSlashStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSlashStartStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSlashStartEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_SLASH"
		, std::bind(&Grimm::GrimmBattleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSlashStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSlashEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_SLASH_UP"
		, std::bind(&Grimm::GrimmBattleSlashUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSlashUpStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSlashUpEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_AIR_DASH_START"
		, std::bind(&Grimm::GrimmBattleAirDashStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleAirDashStartStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleAirDashStartEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_AIR_DASH"
		, std::bind(&Grimm::GrimmBattleAirDashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleAirDashStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleAirDashEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_AIR_DASH_END"
		, std::bind(&Grimm::GrimmBattleAirDashEndtUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleAirDashEndtStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleAirDashEndtEnd, this, std::placeholders::_1));


	GrimmBattleManager_.CreateStateMember("BATTLE_FIRE"
		, std::bind(&Grimm::GrimmBattleFireUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleFireStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleFireEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_SPIKE_START"
		, std::bind(&Grimm::GrimmBattleSpikeStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSpikeStartStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSpikeStartEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_SPIKE"
		, std::bind(&Grimm::GrimmBattleSpikeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattleSpikeStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattleSpikeEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_CAST_START"
		, std::bind(&Grimm::GrimmBattlCastStartUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlCastStartStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlCastStartEnd, this, std::placeholders::_1));
	
	GrimmBattleManager_.CreateStateMember("BATTLE_CAST"
		, std::bind(&Grimm::GrimmBattlCastUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlCastStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlCastEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_CAST_END"
		, std::bind(&Grimm::GrimmBattlCastEndUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlCastEndStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlCastEndEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_STUN"
		, std::bind(&Grimm::GrimmBattlStunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlStunStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlStunEnd, this, std::placeholders::_1));

	GrimmBattleManager_.CreateStateMember("BATTLE_STUN_BAT"
		, std::bind(&Grimm::GrimmBattlStunBatUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Grimm::GrimmBattlStunBatStart, this, std::placeholders::_1)
		, std::bind(&Grimm::GrimmBattlStunBatEnd, this, std::placeholders::_1));


	EventState_ = EventState::Appear;
	GetRenderer()->Off();



	//GrimmFire_->SetParent(this);    

}

void Grimm::Update(float _DeltaTime)
{
	switch (EventState_)
	{
	case EventState::Appear:
		GrimmAppearManager_.Update(_DeltaTime);
		break;
	case EventState::Battle:
		GrimmBattleManager_.Update(_DeltaTime);

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

void Grimm::SetChangeStateString(PatternType _type)
{
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(_type);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

	ChangeState_ = UpperName;
}

void Grimm::SetRamdomPattern()
{
	//PatternRamdom_ = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(PatternType::MAX) - 1);
	////auto Type_ = magic_enum::E

	////if (Ramdom == PrevChangeState_)
	////{

	////}

	//while (PatternRamdom_ == PrevChangeState_)
	//{
	//	PatternRamdom_ = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(PatternType::MAX) - 1);
	//}


	//PrevChangeState_ = PatternRamdom_;
	SetChangeStateString(PatternType::BATTLE_CAST_START);

	//SetChangeStateString(static_cast<PatternType>(PatternRamdom_));
	GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_DISAPPEAR");


}
