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
	KnightManager_()
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

	GetTransform().SetLocalScale({1, 1, 1});
	GetTransform().SetLocalPosition({500, -4500});

	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));

	GetRenderer()->CreateFrameAnimation("STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f));
	GetRenderer()->CreateFrameAnimation("JUMP_ANIMATION", FrameAnimation_DESC("Knight_jump_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimation("FALL_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimation("WALK_ANIMATION", FrameAnimation_DESC("Knight_walk0000-Sheet.png", 0, 7, 0.100f));

	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");

	this->SetMoveDirection(float4::RIGHT);
	this->SetSpeed(200.f);
	this->SetisMove(true);

	KnightManager_.CreateStateMember("STILL", this, &Knight::KnightStillUpdate, &Knight::KnightStillStart);
	KnightManager_.CreateStateMember("WALK", this, &Knight::KnightWalkUpdate, &Knight::KnightWalkStart);
	KnightManager_.CreateStateMember("JUMP", this, &Knight::KnightJumpUpdate, &Knight::KnightJumpStart, &Knight::KnightJumpEnd);
	KnightManager_.CreateStateMember("FALL", this, &Knight::KnightFallUpdate, &Knight::KnightFallStart, &Knight::KnightFallEnd);



	KnightManager_.ChangeState("STILL");

	GravityY = 320.f;
	JumpPower_ = { 150, 0 };
	FallDownDirection_ = { 0, -1, 0 };
	CollisionSize_ = { 349/2, 186/2, 0 };
	FallSpeed_ = 300.f;
}

void Knight::Update(float _DeltaTime)
{
	KnightManager_.Update(_DeltaTime);

}


bool Knight::GetPixelRed(float4 _NextDir)
{
	float4 Color = GetCollisionMap()->GetCurTexture()->GetPixel(GetTransform().GetLocalPosition().ix() + _NextDir.x + CollisionSize_.x, 
		-(GetTransform().GetLocalPosition().iy() + _NextDir.y -  CollisionSize_.y));

	if (Color.CompareInt4D(float4(0, 0, 1, 1)) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Knight::GetisPlayerMove()
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

void Knight::KnightisOnGroundCheck(float _DeltaTime)
{
	if (GetPixelRed(GetKnightNextPos(_DeltaTime)) == true)
	{
		this->SetisGround(true);
		GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);
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
