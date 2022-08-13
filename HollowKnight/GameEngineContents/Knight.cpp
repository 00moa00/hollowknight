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

Knight::Knight()
	:
	KnightManager_(),
	KnightJumpPower_(),
	KnightSlashTimer_(),
	KnightLookUpTimer_(),
	KnightLookDownTimer_(),
	KnightDashTimer_(),
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
	isLandEnd_(false)
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
	SetallDownDirection({ 0, -1, 0 });
	SetCollisionSize({ 0, 0, 0 });
	SetFallSpeed(2);

	SetLeftBottom({ -15.f, 0 , 0,  0 });
	SetRightBottom({ 15.f, 0, 0, 0 });
	SetRightTop({ 15.f, 20.f, 0, 0 });
	SetLeftTop({ -15.f, 20.f, 0, 0 });
	SetCenterTop({ 0, 20.f, 0, 0 });

	CreateCollisionComponent(float4{349, 186, 1}, static_cast<int>(OBJECTORDER::Knight));
	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));

	GetTransform().SetLocalPosition({500,-4000,0});
	
	KnightSlashEffect_ = GetLevel()->CreateActor<KnightSlashEffect>();
	KnightSlashEffect_->SetAnimationStill();

	KnightJumpPower_ = 250.f;
	KnightDoubleJumpPower_ = 180.f;

	//================================
	//    CreateKey
	//================================

	if (false == GameEngineInput::GetInst()->IsKey("KnightLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("KnightLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("KnightRight", 'D');
		GameEngineInput::GetInst()->CreateKey("KnightUp", 'W');
		GameEngineInput::GetInst()->CreateKey("KnightDown", 'S');

		GameEngineInput::GetInst()->CreateKey("KnightRunMode", 'R');

		GameEngineInput::GetInst()->CreateKey("KnightLookMap", VK_TAB);
		GameEngineInput::GetInst()->CreateKey("KnightDash", VK_SHIFT);
		GameEngineInput::GetInst()->CreateKey("KnightFocus", 'Q');

		GameEngineInput::GetInst()->CreateKey("KnightSlash", 'C');

		GameEngineInput::GetInst()->CreateKey("KnightJump", VK_SPACE);

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

	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS_ANIMATION", FrameAnimation_DESC("Knight_focus_v020000-Sheet.png", 0, 11, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("LOW_HEALTH_ANIMATION", FrameAnimation_DESC("Knight_idle_low_health000-Sheet.png", 0, 9, 0.100f));


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





	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");

	//================================
	//    Create Bind Animation
	//================================

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

	

	//================================
	//    Create State
	//================================
	 
	// ---- 기본 ----

	KnightManager_.CreateStateMember("STILL"
		, std::bind(&Knight::KnightStillUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightStillStart, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("WALK"
		, std::bind(&Knight::KnightWalkUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightWalkStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALK_TURN"
		, std::bind(&Knight::KnightWalkTurnUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightWalkTurnStart, this, std::placeholders::_1));


	KnightManager_.CreateStateMember("LOOK_UP"
		, std::bind(&Knight::KnightLookUpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightLookUpStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookUpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LOOK_DOWN"
		, std::bind(&Knight::KnightLookDownUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightLookDownStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookDownEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("JUMP"
		, std::bind(&Knight::KnightJumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_JUMP"
		, std::bind(&Knight::KnightDoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDoubleJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LAND"
		, std::bind(&Knight::KnightLandUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightLandStart, this, std::placeholders::_1), std::bind(&Knight::KnightLandEnd, this, std::placeholders::_1));


	KnightManager_.CreateStateMember("FALL"
		, std::bind(&Knight::KnightFallUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightFallStart, this, std::placeholders::_1), std::bind(&Knight::KnightFallEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DASH"
		, std::bind(&Knight::KnightDashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDashStart, this, std::placeholders::_1), std::bind(&Knight::KnightDashEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("FOCUS"
		, std::bind(&Knight::KnightFocusUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightFocusStart, this, std::placeholders::_1), std::bind(&Knight::KnightFocusEnd, this, std::placeholders::_1));


	// ---- 공격 ----

	KnightManager_.CreateStateMember("SLASH"
		, std::bind(&Knight::KnightSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_SLASH"
		, std::bind(&Knight::KnightDoubleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDoubleSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("UP_SLASH"
		, std::bind(&Knight::KnightUpSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightUpSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightUpSlashEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("DOWN_SLASH"
		, std::bind(&Knight::KnightDownSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDownSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightDownSlashEnd, this, std::placeholders::_1));


	// ---- 달리기 ----

	KnightManager_.CreateStateMember("RUN"
		, std::bind(&Knight::KnightRunUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightRunStart, this, std::placeholders::_1), std::bind(&Knight::KnightRunEnd, this, std::placeholders::_1));


	// ---- 지도 보기 ----

	KnightManager_.CreateStateMember("MAP_STILL"
		, std::bind(&Knight::KnightMapStillUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightMapStillStart, this, std::placeholders::_1), std::bind(&Knight::KnightMapStillEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING"
		, std::bind(&Knight::KnightMapWalkinglUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightMapWalkinglStart, this, std::placeholders::_1), std::bind(&Knight::KnightMapWalkinglEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING_TURN"
		, std::bind(&Knight::KnightMapWalkingTurnlUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightMapWalkingTurnlStart, this, std::placeholders::_1), std::bind(&Knight::KnightMapWalkingTurnlEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_LOOK"
		, std::bind(&Knight::KnightMapSitLooklUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightMapSitLooklStart, this, std::placeholders::_1), std::bind(&Knight::KnightMapSitLooklEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_WRITE"
		, std::bind(&Knight::KnightMapSitWritelUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightMapSitWritelStart, this, std::placeholders::_1), std::bind(&Knight::KnightMapSitWritelEnd, this, std::placeholders::_1));



	KnightManager_.ChangeState("STILL");


}

void Knight::Update(float _DeltaTime)
{
	KnightManager_.Update(_DeltaTime);

	std::string a = "";
	if (isPressJumppingKey_ == true)
	{
		a = "true";
	}
	else
	{
		a = "false";

	}

	GameEngineDebug::OutPutString(a);
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
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalPositiveX();

		this->SetMoveDirection(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
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
		KnightSlashEffect_->GetTransform().PixLocalPositiveX();
		ActtingMoveDirection_ = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetTransform().PixLocalNegativeX();

		ActtingMoveDirection_ = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		ActtingMoveDirection_ = float4::DOWN;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		ActtingMoveDirection_ = float4::UP;
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
