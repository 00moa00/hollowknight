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
	isKnightActtingMove_(false)
{
}

Knight::~Knight()
{
}

void Test2Start(const FrameAnimation_DESC& _Info)
{
	GameEngineDebug::OutPutString("스타트\n");
}

void Test2End(const FrameAnimation_DESC& _Info)
{
	GameEngineDebug::OutPutString("앤드\n");
}

void Test2Frame(const FrameAnimation_DESC& _Info)
{
	// GameEngineDebug::OutPutString("프레임\n");
}

void Test2Time(const FrameAnimation_DESC& _Info, float _Time)
{
	// GameEngineDebug::OutPutString("타임\n");
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
	}


	//GetTransform().SetLocalScale({ 1, 1, 1 });

	CreateRendererComponent(float4{ 349, 186, 0 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));
	GetTransform().SetWorldPosition({ 500, -4000, 0 });

	GetRenderer()->CreateFrameAnimation("STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f));
	GetRenderer()->CreateFrameAnimation("JUMP_ANIMATION", FrameAnimation_DESC("Knight_jump_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimation("FALL_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimation("WALK_ANIMATION", FrameAnimation_DESC("Knight_walk0000-Sheet.png", 0, 7, 0.100f));

	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");



	KnightManager_.CreateStateMember("STILL", this, &Knight::KnightStillUpdate, &Knight::KnightStillStart);
	KnightManager_.CreateStateMember("WALK", this, &Knight::KnightWalkUpdate, &Knight::KnightWalkStart);
	KnightManager_.CreateStateMember("JUMP", this, &Knight::KnightJumpUpdate, &Knight::KnightJumpStart, &Knight::KnightJumpEnd);
	KnightManager_.CreateStateMember("FALL", this, &Knight::KnightFallUpdate, &Knight::KnightFallStart, &Knight::KnightFallEnd);



	KnightManager_.ChangeState("STILL");

	this->SetMoveDirection(float4::RIGHT);
	this->SetSpeed(300.f);
	this->SetisMove(true);
	this->SetGravity(400.f);
	this->SetJumpPower({ 300, 0 });
	this->SetJumpSpeed(5);
	this->SetallDownDirection({ 0, -1, 0 });
	this->SetCollisionSize({ 0, 0, 0 });
	this->SetFallSpeed(2);
}

void Knight::Update(float _DeltaTime)
{
	KnightManager_.Update(_DeltaTime);

}


bool Knight::GetPixelRed(float4 _NextDir)
{
	float4 Color = GetCollisionMap()->GetCurTexture()->GetPixel(GetTransform().GetLocalPosition().ix() + _NextDir.x + GetCollisionSize().x,
		-(GetTransform().GetLocalPosition().iy() + _NextDir.y - GetCollisionSize().y));

	if (Color.CompareInt4D(float4(0, 0, 1, 1)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
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

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		return true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		return true;
	}

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
		this->AddMoveDirection(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		this->AddMoveDirection(float4::RIGHT);

	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		this->AddMoveDirection(float4::DOWN);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		this->AddMoveDirection(float4::UP);
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

void Knight::KnightisOnGroundCheck(float _DeltaTime)
{
	if (GetPixelRed(GetKnightNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
	}

	else
	{
		this->SetisGround(false);
	}

}

float4 Knight::GetKnightNextPos(float4 _DeltaTime)
{
	this->SetMoveDirectionNormalize();
	return (GetMoveDirection() * _DeltaTime * GetSpeed());
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
