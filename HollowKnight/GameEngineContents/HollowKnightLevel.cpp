#include "PreCompile.h"
#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>

HollowKnightLevel::HollowKnightLevel() 
	:
	MasterMap_(nullptr),
	BackgroundRenderer_(nullptr),
	Knight_(nullptr),
	HUD_(nullptr),
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

void HollowKnightLevel::CreateKingsPass1Monster()
{
	Crawlid_ = CreateActor<Crawlid>();
}

void HollowKnightLevel::CreateUIActor()
{
	HUD_ = CreateActor<HUD>();
}


void HollowKnightLevel::CameraMoveWindowLimit()
{
	//카메라가 없다면
	if (GetMainCameraActor() == nullptr)
	{
		return;
	}

	//카메라는 플레이어를 따라간다.
	//GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
	//MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();

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
		MainCameraPosition_.y = -(MainMapSize_.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}

}


void HollowKnightLevel::CameraMoveKnightLimit()
{

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


	if (GetMainCameraActor() == nullptr)
	{
		return;
	}

	GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
	//MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();

//	float4 KnightPosition = Knight_->GetTransform().GetLocalPosition();
//
//
//	float DOWNY = -(MainMapSize_.y - (GameEngineWindow::GetInst()->GetScale().hiy()+100));
//	float UPY = GameEngineWindow::GetInst()->GetScale().hiy();
//	float RIGHTX = (MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix());
//	float LEFTX = GameEngineWindow::GetInst()->GetScale().hix();
//
//	if (KnightPosition.y < UPY
//		&& KnightPosition.y  > DOWNY
///*		&& KnightPosition.x < RIGHTX
//		&& KnightPosition.x > LEFTX*/)
//	{
//		GetMainCameraActorTransform().SetLocalPosition(KnightPosition);
//		MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
//	}


}

void HollowKnightLevel::SetMainMapSize(float4 _MapSize)
{
	MainMapSize_ = _MapSize;

}

