#include "PreCompile.h"

#include <iostream>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

#include "Knight.h"
#include "MasterMap.h"

#include "KnightData.h"

#include "MasterNPC.h"
#include "RoomPotal.h"

#include "MonsterHitEffect.h"


Knight::Knight()
	:
	KnightManager_(),

	KnightJumpPower_(),

	KnightSlashTimer_(0.0f),
	KnightLookUpTimer_(0.0f),
	KnightLookDownTimer_(0.0f),
	KnightDashTimer_(0.0f),
	KnightSlashCollisionTimer_(0.0f),
	KnihgtInvincibilityTimer_(0.0f),
	KnihgtInvincibilitingTimer_(0.0f),

	isPossibleDoubleSlash_(false),
	isKnightActtingMove_(false),
	isPressJumppingKey_(false),
	isSlashEnd_(false),
	isDoubleSlashEnd_(false),
	isPossibleDoubleJump_(false),
	isDoubleJumpEnd_(false),
	isUpSlashEnd_(false),
	isDownSlashEnd_(false),
	isLookMap_(false),
	isWalkTurnEnd_(false),
	isRunMode_(false),
	isFocusEnd_(false),
	isLowHealth_(false),
	isLandEnd_(false),
	isStunEnd_(false),
	isDeath_(false),
	isDeathEnd_(false),
	isSitEnd_(false),
	isDoorEnd_(false),

	isInvincibility_(false),
	isKnightBlack_(false),

	KnightSlashEffect_(nullptr),
	KnightStunEffect_(nullptr),
	SideDarkEffect_(nullptr),
	KnightSiblingLightEffect_(nullptr),
	KnightDonutLightEffect_(nullptr),
	KnightMainLightEffect_(nullptr),

	ChangeLevel_(""),

	KnockbackDirection_(float4::ZERO)
{
}

Knight::~Knight()
{
}




void Knight::Start()
{	
	
	//================================
	//    Initialize
	//================================
	SetMoveDirection(float4::RIGHT);
	SetSpeed(300.f);
	SetisMove(true);
	SetGravity(400.f);
	SetJumpPower({ 300, 0 });
	SetJumpSpeed(5);
	SetCollisionSize({ 0, 0, 0 });
	SetFallSpeed(2);

	SetLeftBottom({ -15.f, 0 , 0,  0 });
	SetRightBottom({ 15.f, 0, 0, 0 });
	SetRightTop({ 15.f, 20.f, 0, 0 });
	SetLeftTop({ -15.f, 20.f, 0, 0 });
	SetCenterTop({ 0, 20.f, 0, 0 });
	SetLeftCenter({-30.f, 100.f, 0});
	SetRightCenter({ 30.f, 100.f, 0 });
	SetCenter({0, 20.f, 0, 0});

	CreateCollisionComponent(float4{60, 120, 1}, static_cast<int>(COLLISION_ORDER::Knight));
	GetCollision()->GetTransform().SetWorldPosition({0, 120/2, static_cast<float>(Z_ORDER::Knight) });

	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));
	
	GetRenderer()->GetTransform().PixLocalNegativeX();


	Test1_ = CreateComponent<GameEngineCollision>();
	Test1_->GetTransform().SetLocalScale({ 15,15,1 });

	Test2_ = CreateComponent<GameEngineCollision>();
	Test2_->GetTransform().SetLocalScale({ 15,15,1 });

	GetTransform().SetWorldPosition({500,-4000,static_cast<float>(Z_ORDER::Knight) });
	
	KnightSlashEffect_ = GetLevel()->CreateActor<KnightSlashEffect>();
	KnightMainLightEffect_ = GetLevel()->CreateActor<KnightMainLightEffect>();
	KnightDonutLightEffect_ = GetLevel()->CreateActor<KnightDonutLightEffect>();
	KnightSiblingLightEffect_ = GetLevel()->CreateActor<KnightSiblingLightEffect>();
	KnightStunEffect_ = GetLevel()->CreateActor<KnightStunEffect>();
	KnightStunEffect_->StunEffectOff();



	//SideDarkEffect_ = GetLevel()->CreateActor<SideDarkEffect>();
	KnightSlashEffect_->SetAnimationStill();

	KnightJumpPower_ = 250.f;
	KnightDoubleJumpPower_ = 180.f;

	//================================
	//    CreateKey
	//================================

	if (false == GameEngineInput::GetInst()->IsKey("KnightLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("KnightLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("KnightRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("KnightUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("KnightDown", VK_DOWN);

		GameEngineInput::GetInst()->CreateKey("KnightRunMode", 'R');

		GameEngineInput::GetInst()->CreateKey("KnightLookMap", VK_TAB);
		GameEngineInput::GetInst()->CreateKey("KnightDash", VK_SHIFT);
		GameEngineInput::GetInst()->CreateKey("KnightFocus", 'Q');

		GameEngineInput::GetInst()->CreateKey("KnightSlash", 'C');
		GameEngineInput::GetInst()->CreateKey("KnightTalking", 'Z');
		GameEngineInput::GetInst()->CreateKey("KnightClose", 'Z');

		GameEngineInput::GetInst()->CreateKey("KnightSit", 'T');

		GameEngineInput::GetInst()->CreateKey("KnightJump", VK_SPACE);

		GameEngineInput::GetInst()->CreateKey("OnOffSettingPage", 'I');

	}


	//================================
	//    Create Animation
	//================================
 
	// ---- 기본 ----
	GetRenderer()->CreateFrameAnimationCutTexture("STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f));
	
	GetRenderer()->CreateFrameAnimationCutTexture("JUMP_ANIMATION", FrameAnimation_DESC("Knight_jump_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_JUMP_ANIMATION", FrameAnimation_DESC("Knight_double_jump_v020000-Sheet.png", 0, 7, 0.100f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("FALL_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("LAND_ANIMATION", FrameAnimation_DESC("Knight_land0000-Sheet.png", 0, 2, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("WALK_ANIMATION", FrameAnimation_DESC("Knight_walk0000-Sheet.png", 0, 7, 0.100f));
	
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_TURN_LEFT_ANIMATION", FrameAnimation_DESC("Knight_turn000-Sheet.png", 0, 0, 0.050f, false ));
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Knight_turn000-Sheet.png", 1, 1, 0.050f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("LOOK_DOWN_ANIMATION", FrameAnimation_DESC("Knight_look_down0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("LOOK_UP_ANIMATION", FrameAnimation_DESC("Knight_look_up0000-Sheet.png", 0, 5, 0.100f, false));
	
	GetRenderer()->CreateFrameAnimationCutTexture("DASH_ANIMATION", FrameAnimation_DESC("Knight_dash_v020000-Sheet.png", 0, 11, 0.070f, false));


	GetRenderer()->CreateFrameAnimationCutTexture("LOW_HEALTH_ANIMATION", FrameAnimation_DESC("Knight_idle_low_health000-Sheet.png", 0, 9, 0.100f));
	
	// ---- 스턴 ----
	GetRenderer()->CreateFrameAnimationCutTexture("STUN_ANIMATION", FrameAnimation_DESC("Knight_stun0000-Sheet.png", 0, 4, 0.070f, false));

	// ---- 죽음 ----
	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Knight_death_anim0000-Sheet.png", 0, 13, 0.070f, false));


	// ---- 달리기 ----
	GetRenderer()->CreateFrameAnimationCutTexture("RUN_ANIMATION", FrameAnimation_DESC("Knight_run0000-Sheet.png", 0, 7, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_TO_RUN_ANIMATION", FrameAnimation_DESC("Knight_idle_to_run0000-Sheet.png", 0, 4, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("RUN_TO_IDLE_ANIMATION", FrameAnimation_DESC("Knight_run_to_idle000-Sheet.png", 0, 5, 0.100f, false));

	// ---- 지도 보기 ----
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_OPEN_ANIMATION", FrameAnimation_DESC("Knight_idle_map0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_map0000-Sheet.png", 2, 8, 0.100f));
	
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_OPEN_WALKING_ANIMATION", FrameAnimation_DESC("Knight_walk_map0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_ANIMATION", FrameAnimation_DESC("Knight_walk_map0000-Sheet.png", 2, 9, 0.100f));

	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Knight_walk_map_turn0000-Sheet.png", 0, 0, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_TURN_LEFT_ANIMATION", FrameAnimation_DESC("Knight_walk_map_turn0000-Sheet.png", 1, 1, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("MAP_SIT_WRITE_ANIMATION", FrameAnimation_DESC("Knight_sit_map_write0000-Sheet.png", 0, 3, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_SIT_LOOK_ANIMATION", FrameAnimation_DESC("Knight_sit_map_look0026-Sheet.png", 0, 3, 0.100f));

	// ---- 공격 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 6, 10, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("UP_SLASH_ANIMATION", FrameAnimation_DESC("Knight_up_slash0000-Sheet.png", 0, 4, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("DOWN_SLASH_ANIMATION", FrameAnimation_DESC("Knight_down_slash_v02000-Sheet.png", 0, 4, 0.100f));
	
	// ---- 기상 ----
	GetRenderer()->CreateFrameAnimationCutTexture("WAKEUP_GROUND_ANIMATION", FrameAnimation_DESC("Knight_wake_up_ground0000-Sheet.png", 0, 20, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("WAKEUP_ANIMATION", FrameAnimation_DESC("Knight_wake0000-Sheet.png", 0, 4, 0.100f, false));

	// ---- 탈진 ----
//	GetRenderer()->CreateFrameAnimationCutTexture("LOW_HEALTH_ANIMATION", FrameAnimation_DESC("Knight_idle_low_health000-Sheet.png", 0, 9, 0.100f));



	// ---- 슬라이드 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SLIDE_ANIMATION", FrameAnimation_DESC("Knight_wall_slide0000-Sheet.png", 0, 3, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("WALL_JUMP_ANIMATION", FrameAnimation_DESC("Knight_wall_jump0000-Sheet.png", 0, 2, 0.100f));

	// ---- 의자 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SIT_ANIMATION", FrameAnimation_DESC("Knight_sit0000-Sheet.png", 0, 4, 0.070f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SIT_IDLE_ANIMATION", FrameAnimation_DESC("Knight_sit0000-Sheet.png", 3, 3, 0.100f));
	
	GetRenderer()->CreateFrameAnimationCutTexture("DOOR_ANIMATION", FrameAnimation_DESC("Knight_into_door0000-Sheet.png", 0, 9, 0.100f, false));


	// ---- 집중 ----

	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS_ANIMATION", FrameAnimation_DESC("Knight_focus_v020000-Sheet.png", 0, 11, 0.100f, false));



	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
	//GetRenderer()->GetPipeLine()->SetOutputMergerBlend("LightenBlend");

	//================================
	//    Create Bind Animation
	//================================

	GetRenderer()->AnimationBindEnd("SIT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("SIT_IDLE_ANIMATION");

		});


	GetRenderer()->AnimationBindEnd("SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isSlashEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DOUBLE_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDoubleSlashEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DOUBLE_JUMP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDoubleJumpEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("UP_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isUpSlashEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DOWN_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDownSlashEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MAP_OPEN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("MAP_STILL_ANIMATION");
		});

	GetRenderer()->AnimationBindEnd("MAP_OPEN_WALKING_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
		});

	GetRenderer()->AnimationBindEnd("MAP_WALKING_TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isMapWalkTurnEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("MAP_WALKING_TURN_LEFT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isMapWalkTurnEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("WALK_TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isWalkTurnEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("WALK_TURN_LEFT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isWalkTurnEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("IDLE_TO_RUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("RUN_ANIMATION"); 
		});

	GetRenderer()->AnimationBindEnd("RUN_TO_IDLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
		});

	GetRenderer()->AnimationBindEnd("FOCUS_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isFocusEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("LAND_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isLandEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("STUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isStunEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DEATH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDeathEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("WAKEUP_GROUND_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isGroundWakeUpEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("WAKEUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isWakeUpEnd_ = true;
		});

	GetRenderer()->AnimationBindEnd("DOOR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			isDoorEnd_ = true;
		});
	//================================
	//    Create State
	//================================
	 
	// ---- 기본 ----
	KnightManager_.CreateStateMember("STILL"
		, std::bind(&Knight::KnightStillUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightStillStart, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("WALK"
		, std::bind(&Knight::KnightWalkUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWalkStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALK_TURN"
		, std::bind(&Knight::KnightWalkTurnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWalkTurnStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LOOK_UP"
		, std::bind(&Knight::KnightLookUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLookUpStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookUpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LOOK_DOWN"
		, std::bind(&Knight::KnightLookDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLookDownStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookDownEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("JUMP"
		, std::bind(&Knight::KnightJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_JUMP"
		, std::bind(&Knight::KnightDoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoubleJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LAND"
		, std::bind(&Knight::KnightLandUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLandStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightLandEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("FALL"
		, std::bind(&Knight::KnightFallUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Knight::KnightFallStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightFallEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DASH"
		, std::bind(&Knight::KnightDashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDashEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("FOCUS"
		, std::bind(&Knight::KnightFocusUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightFocusStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightFocusEnd, this, std::placeholders::_1));


	// ---- 공격 ----
	KnightManager_.CreateStateMember("SLASH"
		, std::bind(&Knight::KnightSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_SLASH"
		, std::bind(&Knight::KnightDoubleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoubleSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDoubleSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("UP_SLASH"
		, std::bind(&Knight::KnightUpSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightUpSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightUpSlashEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("DOWN_SLASH"
		, std::bind(&Knight::KnightDownSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDownSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDownSlashEnd, this, std::placeholders::_1));
	
	// ----스턴 ----
	KnightManager_.CreateStateMember("STUN"
		, std::bind(&Knight::KnightStunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightStunStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightStunEnd, this, std::placeholders::_1));

	// ---- 사망 ----
	KnightManager_.CreateStateMember("DEATH"
		, std::bind(&Knight::KnightDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDeathStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDeathEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("WAKE_UP"
		, std::bind(&Knight::KnightWakeUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWakeUpStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWakeUpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("GROUND_WAKE_UP"
		, std::bind(&Knight::KnightWakeUpGroundUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWakeUpGroundStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWakeUpGroundEnd, this, std::placeholders::_1));


	// ---- 달리기 ----
	KnightManager_.CreateStateMember("RUN"
		, std::bind(&Knight::KnightRunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightRunStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightRunEnd, this, std::placeholders::_1));


	// ---- 지도 보기 ----
	KnightManager_.CreateStateMember("MAP_STILL"
		, std::bind(&Knight::KnightMapStillUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapStillStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapStillEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING"
		, std::bind(&Knight::KnightMapWalkinglUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapWalkinglStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapWalkinglEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING_TURN"
		, std::bind(&Knight::KnightMapWalkingTurnlUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapWalkingTurnlStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapWalkingTurnlEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_LOOK"
		, std::bind(&Knight::KnightMapSitLooklUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapSitLooklStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapSitLooklEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_WRITE"
		, std::bind(&Knight::KnightMapSitWritelUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapSitWritelStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapSitWritelEnd, this, std::placeholders::_1));


	// ---- 슬라이드 ----
	KnightManager_.CreateStateMember("SLIDE"
		, std::bind(&Knight::KnightSlideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSlideStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSlideEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALL_JUMP"
		, std::bind(&Knight::KnightWallJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWallJumpStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWallJumpEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("WALL_JUMP_LAND"
		, std::bind(&Knight::KnightWallJumpLandUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWallJumpLandStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWallJumpLandEnd, this, std::placeholders::_1));

	// ---- 의자 ----
	KnightManager_.CreateStateMember("SIT"
		, std::bind(&Knight::KnightSitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSitStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSitEnd, this, std::placeholders::_1));


	// ---- NPC 대화 ----
	KnightManager_.CreateStateMember("TALKING"
		, std::bind(&Knight::KnightTalkingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightTalkingStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightTalkingEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SHOPPING"
		, std::bind(&Knight::KnightShoppingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightShoppingStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightShoppingEnd, this, std::placeholders::_1));

	// ---- 문 들어가기 ----
	KnightManager_.CreateStateMember("DOOR"
		, std::bind(&Knight::KnightDoorUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoorStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDoorEnd, this, std::placeholders::_1));

	KnightManager_.ChangeState("FALL");

	ContentsFontRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
	ContentsFontRenderer_->CreateFontRenderer("가나다라마.바사", 24, {500,500}, false, 4);
	ContentsFontRenderer_->FontOn();


}

void Knight::Update(float _DeltaTime)
{
	ContentsFontRenderer_->SetActorToScreenPosition(GetTransform().GetWorldPosition(), GetLevel()->GetMainCameraActorTransform().GetWorldPosition());
	KnightManager_.Update(_DeltaTime);

	if (KnightMainLightEffect_ != nullptr)
	{
		KnightMainLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Light) });	
	}

	if (KnightDonutLightEffect_ != nullptr)
	{
		KnightDonutLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Dount_Light) });
	}

	if (KnightSiblingLightEffect_ != nullptr)
	{
		KnightSiblingLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Small_Light) });
	}
	//SideDarkEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Side_Dark) });
}

void Knight::LevelStartEvent()
{

	


}




bool Knight::GetisKnightMove()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		return true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		return true;
	}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	//{
	//	return true;
	//}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	//{
	//	return true;
	//}

	return false;
}

void Knight::isKnihgtActtingMoveChack()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		isKnightActtingMove_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		isKnightActtingMove_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		isKnightActtingMove_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		isKnightActtingMove_ = true;
	}

	isKnightActtingMove_ = false;
}

void Knight::KnightDirectionCheck()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalPositiveX();

		this->SetMoveDirection(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalNegativeX();


		this->SetMoveDirection(float4::RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		this->SetMoveDirection(float4::DOWN);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		this->SetMoveDirection(float4::UP);
	}
}

void Knight::KnightActtingDirectionCheck()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
		ActtingMoveDirection_ = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();

		ActtingMoveDirection_ = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		//ActtingMoveDirection_ = float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		//ActtingMoveDirection_ = float4::UP;
	}
}

void Knight::KnihgtSlideNegativeRenderer()
{
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

}

void Knight::KnihgtSlidePositiveRenderer()
{
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}
}

void Knight::KnightInvincibiliting(float _DeltaTime)
{
	KnihgtInvincibilitingTimer_ += _DeltaTime;
	KnihgtInvincibilityTimer_ += _DeltaTime;



	if (KnihgtInvincibilityTimer_ > 1.f)
	{
		KnihgtInvincibilityTimer_ = 0.0f;
		isInvincibility_ = false;
		GetRenderer()->GetPixelData().MulColor.r = 1.f;
		GetRenderer()->GetPixelData().MulColor.g = 1.f;
		GetRenderer()->GetPixelData().MulColor.b = 1.f;
	}

	if (KnihgtInvincibilitingTimer_ > 0.1f)
	{
		isKnightBlack_ = !isKnightBlack_;
		KnihgtInvincibilitingTimer_ = 0.0f;
	}
	if (isKnightBlack_ == true && isInvincibility_ == true)
	{
		GetRenderer()->GetPixelData().MulColor.r = 1.f;
		GetRenderer()->GetPixelData().MulColor.g = 1.f;
		GetRenderer()->GetPixelData().MulColor.b = 1.f;
	}

	else if (isKnightBlack_ == false && isInvincibility_ == true)
	{
		GetRenderer()->GetPixelData().MulColor.r = 0.f;
		GetRenderer()->GetPixelData().MulColor.g = 0.f;
		GetRenderer()->GetPixelData().MulColor.b = 0.f;
	}

}

void Knight::KnightIsActtingCheck()
{
	if (false == GameEngineInput::GetInst()->IsPress("KnightLeft")
		&& false == GameEngineInput::GetInst()->IsPress("KnightRight")
		&& false == GameEngineInput::GetInst()->IsPress("KnightDown")
		&& false == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		ActtingMoveDirection_ = float4::ZERO;
	}
}

void Knight::Walkking(float _DeltaTime)
{
	this->KnightDirectionCheck();
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}


	else
	{
		KnightManager_.ChangeState("FALL");
	}

}

void Knight::DoubleSlashTimer(float _DeltaTime)
{
	if (isPossibleDoubleSlash_ == true)
	{
		KnightSlashTimer_ += _DeltaTime;

		if (KnightSlashTimer_ > 0.5f)
		{
			KnightSlashTimer_ = 0.f;
			isPossibleDoubleSlash_ = false;
		}
	}
}

void Knight::LookUpTimerAndChangeState(float _DeltaTime)
{
	KnightLookUpTimer_ += _DeltaTime;

	if (KnightLookUpTimer_ > 0.5f)
	{
		KnightLookUpTimer_ = 0.f;
		KnightManager_.ChangeState("LOOK_UP");
	}
}

void Knight::LookDownTimerAndChangeState(float _DeltaTime)
{

	KnightLookDownTimer_ += _DeltaTime;

	if (KnightLookDownTimer_ > 0.5f)
	{
		KnightLookDownTimer_ = 0.f;
		KnightManager_.ChangeState("LOOK_DOWN");
	}
}

bool Knight::KnightVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (isInvincibility_ == false)
	{
		MasterActor* Monster = dynamic_cast<MasterActor*>(_Other->GetActor());
		MonsterHitEffect* Effect = GetLevel()->CreateActor<MonsterHitEffect>();

		Effect->GetTransform().SetWorldPosition({ Monster->GetTransform().GetWorldPosition().x,  Monster->GetTransform().GetWorldPosition().y + (Monster->GetRenderer()->GetTransform().GetWorldScale().y / 4) , static_cast<float>(Z_ORDER::Effect) });

		if (Monster != nullptr)
		{
			KnockbackDirection_ = Monster->GetMoveDirection();
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool Knight::KnihgtVSBenchCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

bool Knight::KnihgtVSNPCCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

	if (NPC != nullptr)
	{

		if (true == GameEngineInput::GetInst()->IsDown("KnightUp"))
		{
			if (NPC->GetNPCType() == NPC_TYPE::Shop)
			{
				NPC->GetMoveDirection().Normalize();
				if (NPC->GetMoveDirection().y < 0)
				{
					NPC->SetisShop(true);
					KnightManager_.ChangeState("SHOPPING");
					//NPC->SetisShop(true);
				}

				else if (NPC->GetMoveDirection().y > 0)
				{
					NPC->SetisTalking(true);
					NPC->GetDialogueSet()->SetDialogueOn();
					KnightManager_.ChangeState("TALKING");
				}

			}

			else if (NPC->GetNPCType() == NPC_TYPE::Normal)
			{
				KnightManager_.ChangeState("TALKING");
				NPC->SetisTalking(true);
				NPC->GetDialogueSet()->SetDialogueOn();
				isTalkingNPC_ = true;

			}
		}
	}

	return true;
}

bool Knight::NPCNextDialogueCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

	if (NPC != nullptr)
	{
		if (true == GameEngineInput::GetInst()->IsDown("KnightTalking"))
		{
			if (NPC->GetDialogueSet()->GetDialougueFull() == true)
			{
				NPC->GetDialogueSet()->SetDialogueOff();
				NPC->SetisTalking(false);
				KnightManager_.ChangeState("STILL");
				//return;
			}

			else
			{
				NPC->GetDialogueSet()->SetNextDialogue();

			}

		}
	}

	return true;
}

bool Knight::ShopCloseCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (GameEngineInput::GetInst()->IsDown("KnightClose") == true)
	{
		MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

		if (NPC != nullptr)
		{

			NPC->SetisShop(false);
			KnightManager_.ChangeState("STILL");
		}
	}

	return false;
}

bool Knight::KnightVSPotalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{

	if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
	{
		RoomPotal* Potal = dynamic_cast<RoomPotal*>(_Other->GetActor());


		POTAL_TYPE FindType = Potal->GetPotalType();

		switch (FindType)
		{
		case POTAL_TYPE::Sly_Shop:
			ChangeLevel_ = "SlyShopLevel";

			break;
		case POTAL_TYPE::Map_Shop:
			ChangeLevel_ = "MapShopLevel";

			break;

		case POTAL_TYPE::Dirt:
			ChangeLevel_ = "DirtmouthLevel2";

			break;
		default:
			break;
		}

		KnightManager_.ChangeState("DOOR");
	}

	return true;
}




//bool Knight::CheckMapCollision()
//{
//
//	std::vector<GameEngineTextureRenderer*> MapCollTexture = GetLevel<MasterMap>()->GetCollisionMap();
//
//	for (std::vector<GameEngineTextureRenderer*>::iterator Start = MapCollTexture.begin(); Start != MapCollTexture.end(); ++Start)
//	{
//		MapCollisionColor_.push_back((*Start)->GetCurTexture()-> GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy()));
//
//		if (false == MapCollisionColor_.begin()->CompareInt4D(float4::ZERO))
//		{
//			int a = 0;
//		}
//
//		return true;
//	}
//
//	return true;
//
//}
