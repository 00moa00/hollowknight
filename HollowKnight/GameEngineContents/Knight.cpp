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
	Speed_(200.0f),
	MoveDirection_(float4::RIGHT),
	MapCollisionColorList_()
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
		GameEngineInput::GetInst()->CreateKey("KnightF", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("KnightB", VK_NUMPAD2);
	}

	GetTransform().SetLocalScale({1, 1, 1});
	GetTransform().SetLocalPosition({500, -5000});
	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	

	//SetCollisionMap(GetLevel<MasterMap>()->GetCollisionMap());
}

void Knight::Update(float _DeltaTime)
{

	//CheckMapCollision();
	//float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();
	//float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition();


	float4 NextPos;
	float4 CheckPos = MoveDirection_;
	float4 Move = float4::ZERO;



	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
		GetRenderer()->GetTransform().PixLocalPositiveX();
		MoveDirection_ += float4::LEFT;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
		GetRenderer()->GetTransform().PixLocalNegativeX();
		MoveDirection_ += float4::RIGHT;

	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
		MoveDirection_ += float4::UP;

	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
		MoveDirection_ += float4::DOWN;
	}

	MoveDirection_.Normalize();
	//NextPos.x = + (MoveDirection_ * _DeltaTime * Speed_);

	float4 Color = GetCollisionMap()->GetCurTexture()->GetPixel(GetTransform().GetLocalPosition().ix(), -GetTransform().GetLocalPosition().iy());
	//bgra
	if (false == Color.CompareInt4D(float4(0, 0, 1, 1)))
	{
		int a = 0;
	}

}

void Knight::MapCollisionLoad()
{


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
