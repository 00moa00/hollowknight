#include "PreCompile.h"
#include "AllLocalMap.h"
#include "HollowKnightLevel.h"

AllLocalMap::AllLocalMap() 
	:
	MapBack_(nullptr)
{
}

AllLocalMap::~AllLocalMap() 
{
}

void AllLocalMap::Start()
{
	MapBack_ = GetLevel()->CreateActor<Map>();

	MapBack_->CreateRendererComponent("black2.png");
	MapBack_->GetTransform().SetWorldScale({3000.f, 3000.f});
	MapBack_->GetRenderer()->GetPixelData().MulColor.a = 0.8f;
	MapBack_->Off();
	//================================
	//    CreateKey
	//================================

	if (false == GameEngineInput::GetInst()->IsKey("MapMoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MapMoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MapMoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MapMoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MapMoveDown", VK_DOWN);
	}
}

void AllLocalMap::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsPress("MapMoveLeft") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveLeft();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveRight") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveRight();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveUp") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveTop();

	}

	if (GameEngineInput::GetInst()->IsPress("MapMoveDown") == true)
	{
		GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapMoveDown();

	}
}

void AllLocalMap::OpenAllLocalMap(float4 _Pivot)
{
	GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->On();
	GetLevel<HollowKnightLevel>()->GetDirtmouthMap()->On();
	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetWidePivot(_Pivot);
	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraWide();
	MapBack_->On();


}

void AllLocalMap::CloseAllLocalMap()
{
	GetLevel<HollowKnightLevel>()->GetMapCameraManager()->SetMapCameraNarrow();
	MapBack_->Off();
	//GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->Off();
}

