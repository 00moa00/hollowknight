#include "PreCompile.h"
#include "Knight.h"
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

Knight::Knight() 
	: Speed(200.0f)
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
	GetTransform().SetLocalPosition({300, -1500});
	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 0, static_cast<int>(RENDERORDER::Knight));
	
}

void Knight::Update(float _DeltaTime)
{
	//float4 Test1 = GetLevel()->GetMainCamera()->GetScreenPosition();
	//float4 Test2 = GetLevel()->GetMainCamera()->GetMouseWorldPosition();

	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightF"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("KnightB"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
	}


	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(GetTransform().GetLocalPosition());
}