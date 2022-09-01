#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>

#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include "PointActorComponent.h"
#include "KnightData.h"
#include "ItemSlot.h"

HollowKnightLevel::HollowKnightLevel() 
	:
	MasterMap_(nullptr),
	BackgroundRenderer_(nullptr),
	Knight_(nullptr),
	HUD_(nullptr),
	SettingPage_(nullptr),
	MainCameraPosition_()
{

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::MAPCAMERA);
	}
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

void HollowKnightLevel::CreateKnightShadowActor()
{
	CurKnightShadow_ = CreateActor<KnightShadow>();
}

void HollowKnightLevel::CreateSettingPageActor()
{
	SettingPage_ = CreateActor<SettingPage>();
}

void HollowKnightLevel::CreateForgottenCrossroadMap()
{
	ForgottenCrossroadMap_ = CreateActor<ForgottenCrossroadMap>();
}

void HollowKnightLevel::PushPointActorCharm(int _Order, PointActorComponent* _PointActorComponent)
{	
	PointActorListCharm.insert({ _Order, _PointActorComponent });
}

void HollowKnightLevel::PushPointActorMonsterBook(int _Order, PointActorComponent* _PointActorComponent)
{
	PointActorListMonsterBook.insert({ _Order, _PointActorComponent });
}

void HollowKnightLevel::PushPointActorMap(int _Order, PointActorComponent* _PointActorComponent)
{
	PointActorListMap.insert({ _Order, _PointActorComponent });
}

void HollowKnightLevel::PushPointActorInventory(int _Order, PointActorComponent* _PointActorComponent)
{
	PointActorListInventory.insert({ _Order, _PointActorComponent });

}

void HollowKnightLevel::PushNotches(Notches* _Notches, float4 _Position)
{
	AllNotes_.push_back(_Notches);
	_Notches->GetTransform().SetLocalPosition(_Position);

}


void HollowKnightLevel::PustItemInventroy(ITEM_LIST _Item)
{
	for (int i = 10; i < 22; ++i)
	{
		PointActorComponent*  findComponent = PointActorListInventory.find(i)->second;
		

		ItemSlot* slot = dynamic_cast<ItemSlot*>(findComponent->GetPointActor());
		if (slot->GetisItem() == false)
		{
			slot->PustItem(i, _Item);
			break;
		}
	}


}

GameEngineCameraActor* HollowKnightLevel::GetMapCameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAPCAMERA)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& HollowKnightLevel::GetMapCameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAPCAMERA)]->GetActor()->GetTransform();
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

	GetMainCameraActorTransform().SetWorldPosition({ Knight_->GetTransform().GetLocalPosition().x, Knight_->GetTransform().GetLocalPosition().y,  -1800.0f });
	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();

	//카메라의 위치 - 윈도우 사이즈의 x가 0이라면
	if ( 0 > MainCameraPosition_.x - GameEngineWindow::GetInst()->GetScale().hix() )
	{
		MainCameraPosition_.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
	}

	if (MainMapSize_.x < MainCameraPosition_.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition_.x = MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
	}

	if (0 < MainCameraPosition_.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
	}

	if (-MainMapSize_.y > MainCameraPosition_.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = -(MainMapSize_.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
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

