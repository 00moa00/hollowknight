#include "PreCompile.h"

#include "MapShopLevel.h"

#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"


MapShopLevel::MapShopLevel() 
	:
	DirtmouthPotal_(nullptr)
{
}

MapShopLevel::~MapShopLevel() 
{
}

void MapShopLevel::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("MapShop_Background.png");
	//GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_2.png");
	GetMasterMap()->CreateMapCollision("MapShop_Coll.png");

	CreateKnightActor(); // 플레이어

	GetMasterMap()->CreateTerrain("MapShop_Terrain.png");
	GetMasterMap()->CreateFrontObject("MapShop_MapObject.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 1920, 1080 });

	GetKnight()->GetTransform().SetLocalPosition({ 800, 0.f, static_cast<float>(Z_ORDER::Knight) });


	DirtmouthPotal_ = CreateActor<RoomPotal>();
	DirtmouthPotal_->CreatePotal(POTAL_TYPE::Dirt, false);
	DirtmouthPotal_->GetTransform().SetWorldPosition({ 400, -870.f });

	Iselda_ = CreateActor<Iselda>();

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
}

void MapShopLevel::Update(float _DeltaTime)
{
//	GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());
}

void MapShopLevel::End()
{
}

void MapShopLevel::LevelStartEvent()
{

}

void MapShopLevel::LevelEndEvent()
{

}

