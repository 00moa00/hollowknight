#include "PreCompile.h"
#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
HollowKnightLevel::HollowKnightLevel() 
	:
	MasterMap_(nullptr),
	Knight_(nullptr),
	MainCameraPosition_()
{
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::CraateMasterMapActor()
{
	MasterMap_ = CreateActor<MasterMap>();

}

void HollowKnightLevel::CreateKnightActor()
{
	Knight_ = CreateActor<Knight>();

}

void HollowKnightLevel::CameraMoveWindowLimit()
{

	//카메라가 없다면
	if (GetMainCameraActor() == nullptr)
	{
		return;
	}

	//카메라는 플레이어를 따라간다.
	GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();

	//카메라의 위치 - 윈도우 사이즈의 x가 0이라면
	if ( 0 > MainCameraPosition_.x - GameEngineWindow::GetInst()->GetScale().hix() )
	{
		MainCameraPosition_.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}

	if (MainMapSize_.x < MainCameraPosition_.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition_.x = MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}



	if (0 < MainCameraPosition_.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}


	if (-MainMapSize_.y > MainCameraPosition_.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = -(MainMapSize_.y - GameEngineWindow::GetInst()->GetScale().hiy());
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}

}

void HollowKnightLevel::SetMainMapSize(float4 _MapSize)
{
	MainMapSize_ = _MapSize;

}

