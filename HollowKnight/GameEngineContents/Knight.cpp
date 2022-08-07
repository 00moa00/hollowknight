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
	KnightAttackTimer_(),
	isPossibleDoubleSlash_(false),
	isKnightActtingMove_(false),
	isPressJumppingKey_(false),
	isSlashEnd_(false),
	isDoubleSlashEnd_(false),
	isPossibleDoubleJump_(false),
	isDoubleJumpEnd_(false)
{
}

Knight::~Knight()
{
}




void Knight::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("KnightLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("KnightLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("KnightRight", 'D');
		GameEngineInput::GetInst()->CreateKey("KnightUp", 'W');
		GameEngineInput::GetInst()->CreateKey("KnightDown", 'S');
		GameEngineInput::GetInst()->CreateKey("KnightJump", VK_SPACE);

		GameEngineInput::GetInst()->CreateKey("KnightSlash", 'C');
	}

	CreateCollisionComponent(float4{349, 186, 1}, static_cast<int>(OBJECTORDER::Knight));
	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));
	KnightSlashEffect_ = GetLevel()->CreateActor<KnightSlashEffect>();
	KnightSlashEffect_->SetAnimationStill();

	GetTransform().SetLocalPosition({500,-4000,0});

	GetRenderer()->CreateFrameAnimationCutTexture("STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("JUMP_ANIMATION", FrameAnimation_DESC("Knight_jump_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_JUMP_ANIMATION", FrameAnimation_DESC("Knight_double_jump_v020000-Sheet.png", 0, 7, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FALL_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_ANIMATION", FrameAnimation_DESC("Knight_walk0000-Sheet.png", 0, 7, 0.100f));


	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 6, 10, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("UP_SLASH_ANIMATION", FrameAnimation_DESC("Knight_up_slash0000-Sheet.png", 0, 4, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("DOWN_SLASH_ANIMATION", FrameAnimation_DESC("Knight_down_slash_v02000-Sheet.png", 0, 4, 0.100f));

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


	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");

	KnightManager_.CreateStateMember("STILL"
		, std::bind(&Knight::KnightStillUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightStillStart, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("WALK"
		, std::bind(&Knight::KnightWalkUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightWalkStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("JUMP"
		, std::bind(&Knight::KnightJumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_JUMP"
		, std::bind(&Knight::KnightDoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDoubleJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("FALL"
		, std::bind(&Knight::KnightFallUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightFallStart, this, std::placeholders::_1), std::bind(&Knight::KnightFallEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SLASH"
		, std::bind(&Knight::KnightSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_SLASH"
		, std::bind(&Knight::KnightDoubleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDoubleSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("UP_SLASH"
		, std::bind(&Knight::KnightUpSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightUpSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightUpSlashEnd, this, std::placeholders::_1));
	
	KnightManager_.CreateStateMember("DOWN_SLASH"
		, std::bind(&Knight::KnightDownSlashUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&Knight::KnightDownSlashStart, this, std::placeholders::_1), std::bind(&Knight::KnightDownSlashEnd, this, std::placeholders::_1));


	KnightManager_.ChangeState("STILL");

	KnightJumpPower_ = 250.f;
	KnightDoubleJumpPower_ = 180.f;

	this->SetMoveDirection(float4::RIGHT);
	this->SetSpeed(300.f);
	this->SetisMove(true);
	this->SetGravity(400.f);
	this->SetJumpPower({ 300, 0 });
	this->SetJumpSpeed(5);
	this->SetallDownDirection({ 0, -1, 0 });
	this->SetCollisionSize({ 0, 0, 0 });
	this->SetFallSpeed(2);

	//Point_.SetLeftBottom(-50.f);
	this->SetLeftBottom({ -15.f, 0 , 0,  0});
	this->SetRightBottom({ 15.f, 0, 0, 0 });
	this->SetRightTop({ 15.f, 20.f, 0, 0  });
	this->SetLeftTop({ -15.f, 20.f, 0, 0 });
	this->SetCenterTop({ 0, 20.f, 0, 0 });

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
		this->SetMoveDirection(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
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
		ActtingMoveDirection_ = float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
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

void Knight::Jumpping()
{
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
		KnightAttackTimer_ += _DeltaTime;

		if (KnightAttackTimer_ > 0.5f)
		{
			KnightAttackTimer_ = 0.f;
			isPossibleDoubleSlash_ = false;
		}
	}{}
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
