#include "PreCompile.h"
#include <GameEngineCore/GameEngineCameraActor.h>

#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include "PointActorComponent.h"
#include "KnightData.h"
#include "ItemSlot.h"
#include "Iselda.h"
#include "Sly.h"

HollowKnightLevel::HollowKnightLevel() 
	:
	
	CharmPageInfo_(nullptr),
	InventoryPageInfo_(nullptr),

	ForgottenCrossroadMap_(nullptr),

	NewKnihgtShadow_(nullptr),
	CurKnightShadow_(nullptr),
	MasterMap_(nullptr),
	BackgroundRenderer_(nullptr),
	Knight_(nullptr),
	HUD_(nullptr),
	SettingPage_(nullptr),
	EffectGUIActor_(nullptr),
	Crawlid_(nullptr),
	MapSmokeMaker_(nullptr),
	DirtmouthMap_(nullptr),
	MainCameraManager_(nullptr),
	MapCameraManager_(nullptr),

	WhiteParicleMaker_(nullptr),

	HeartPiece_(nullptr),

	//EffectGUIActor_(nullptr),

	MainCameraPosition_(),
	MapSize_()
{

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -200.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::VIGNETTE);
	}


	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::MAPCAMERA);
	}

	{
		GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
		CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
		CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		CameraActor->GetCameraComponent()->SetCameraOrder(CAMERAORDER::UICAMERA);
	}
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::CreateDirtmouthMap()
{
	DirtmouthMap_ = CreateActor<DirtmouthMap>();
}

void HollowKnightLevel::CreateAllLocalMap()
{
	AllLocalMap_ = CreateActor<AllLocalMap>();

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

void HollowKnightLevel::CreateKingsPass2Monster()
{
	Crawlid_ = CreateActor<Crawlid>();
	Crawlid_->GetTransform().SetWorldPosition({1256, -2265});

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

void HollowKnightLevel::CreateMainCameraManager()
{
	MainCameraManager_ = CreateActor<MainCameraManager>(static_cast<int>(UPDATE_ORDER::CAMERA));
}

void HollowKnightLevel::CreateMapCameraManager()
{
	MapCameraManager_ = CreateActor<MapCameraManager>(static_cast<int>(UPDATE_ORDER::CAMERA));
}


void HollowKnightLevel::CreateEffectGUIActor()
{
	
	EffectGUIActor_ = CreateActor<EffectGUIActor>();
}

void HollowKnightLevel::CreateIselda()
{
	ShopNPC_ = CreateActor<Iselda>();
}

void HollowKnightLevel::CreateSly()
{
	ShopNPC_ = CreateActor<Sly>();

}

void HollowKnightLevel::CreateMapSmokeMaker()
{
	MapSmokeMaker_ = CreateActor<MapSmokeMaker>();
}

void HollowKnightLevel::CreawteMapWhiteParticleMaker()
{
	WhiteParicleMaker_ = CreateActor<WhiteParicleMaker>();
}

void HollowKnightLevel::CreateHeartPiece()
{
	HeartPiece_ = CreateActor<HeartPiece>();
}

void HollowKnightLevel::CreateCharmPageInfo(GameEngineActor* ParrentPage)
{
	CharmPageInfo_ = CreateActor<SettingPageInfo>();
	CharmPageInfo_->SetParent(ParrentPage);
}

void HollowKnightLevel::CreateInventoryPageInfo(GameEngineActor* ParrentPage)
{
	InventoryPageInfo_ = CreateActor<SettingPageInfo>();
	InventoryPageInfo_->SetParent(ParrentPage);
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

			KnightData::GetInst()->PushKnihgtItemList(_Item);

			break;
		}
	}

}

void HollowKnightLevel::RePustItemInventroy(ITEM_LIST _Item)
{
	for (int i = 10; i < 22; ++i)
	{
		PointActorComponent* findComponent = PointActorListInventory.find(i)->second;


		ItemSlot* slot = dynamic_cast<ItemSlot*>(findComponent->GetPointActor());
		if (slot->GetisItem() == false)
		{
			slot->PustItem(i, _Item);
			break;
		}
	}
}

void HollowKnightLevel::PustDefultItemInventroy(ITEM_LIST _Item)
{
	for (int i = 10; i < 22; ++i)
	{
		PointActorComponent* findComponent = PointActorListInventory.find(i)->second;


		ItemSlot* slot = dynamic_cast<ItemSlot*>(findComponent->GetPointActor());
		if (slot->GetisItem() == false)
		{
			slot->PustItem(i, _Item);
			break;
		}
	}
}

void HollowKnightLevel::AllPopItemInventory()
{
	for (int i = 10; i < 22; ++i)
	{
		PointActorComponent* findComponent = PointActorListInventory.find(i)->second;


		ItemSlot* slot = dynamic_cast<ItemSlot*>(findComponent->GetPointActor());
		if (slot->GetisItem() == true)
		{
			slot->SetisItem(false);
			slot->GetItem()->Death();
			//PointActorListInventory.erase(i);
		}
	}

	//KnightData::GetInst()->GetKnightItemData().clear();

}

GameEngineCameraActor* HollowKnightLevel::GetMapCameraActor()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAPCAMERA)]->GetActor<GameEngineCameraActor>();
}

GameEngineTransform& HollowKnightLevel::GetMapCameraActorTransform()
{
	return Cameras[static_cast<int>(CAMERAORDER::MAPCAMERA)]->GetActor()->GetTransform();
}


//void HollowKnightLevel::CameraMoveWindowLimit()
//{
//	//카메라가 없다면
//	if (GetMainCameraActor() == nullptr)
//	{
//		return;
//	}
//
//	//카메라는 플레이어를 따라간다.
//	//GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
//	//MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
//
//
//	float4 CurrentPos = GetMainCameraActorTransform().GetWorldPosition();
//	float4 DestPos = Knight_->GetTransform().GetWorldPosition();
//	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 10.f);
//
//
//
//	GetMainCameraActorTransform().SetWorldPosition({ MoveCamera.x,MoveCamera.y,  -1800.0f });
//	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
//
//	//카메라의 위치 - 윈도우 사이즈의 x가 0이라면
//	if ( 0 > MainCameraPosition_.x - GameEngineWindow::GetInst()->GetScale().hix() )
//	{
//		MainCameraPosition_.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
//		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
//	}
//
//	if (MainMapSize_.x < MainCameraPosition_.x + GameEngineWindow::GetInst()->GetScale().hix())
//	{
//		MainCameraPosition_.x = MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix();
//		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
//	}
//
//	if (0 < MainCameraPosition_.y + GameEngineWindow::GetInst()->GetScale().hiy())
//	{
//		MainCameraPosition_.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
//		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
//	}
//
//	if (-MainMapSize_.y > MainCameraPosition_.y - GameEngineWindow::GetInst()->GetScale().hiy())
//	{
//		MainCameraPosition_.y = -(MainMapSize_.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
//		GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition_);
//	}
//
//}
//
//
//void HollowKnightLevel::CameraMoveKnightLimit()
//{
//
//	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
//
//
//	if (GetMainCameraActor() == nullptr)
//	{
//		return;
//	}
//
//	GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
//	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
//	//MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
//
////	float4 KnightPosition = Knight_->GetTransform().GetLocalPosition();
////
////
////	float DOWNY = -(MainMapSize_.y - (GameEngineWindow::GetInst()->GetScale().hiy()+100));
////	float UPY = GameEngineWindow::GetInst()->GetScale().hiy();
////	float RIGHTX = (MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix());
////	float LEFTX = GameEngineWindow::GetInst()->GetScale().hix();
////
////	if (KnightPosition.y < UPY
////		&& KnightPosition.y  > DOWNY
/////*		&& KnightPosition.x < RIGHTX
////		&& KnightPosition.x > LEFTX*/)
////	{
////		GetMainCameraActorTransform().SetLocalPosition(KnightPosition);
////		MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();
////	}
//
//
//}

