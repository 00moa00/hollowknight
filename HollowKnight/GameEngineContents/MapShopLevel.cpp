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
#include "BloomPostEffect.h"

#include "ShopLampBug.h"


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
	CreateHeartPiece();

	SetMapSize({ 1920, 1080 });

	GetKnight()->GetTransform().SetLocalPosition({ 800, 0.f, static_cast<float>(Z_ORDER::Knight) });


	DirtmouthPotal_ = CreateActor<RoomPotal>();
	DirtmouthPotal_->CreatePotal(POTAL_TYPE::Grimm_Dirt, false);
	DirtmouthPotal_->GetTransform().SetWorldPosition({ 400, -870.f });

	{
		ShopLampBug* ShopLampBug_ = CreateActor<ShopLampBug>();
		ShopLampBug_->GetTransform().SetWorldPosition({ 959.f, -602.f });
		ShopLampBug_->GetRenderer()->GetTransform().SetWorldScale({ 105.f * 0.8f , 105.f * 0.8f });
	}

	CreateIselda();

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

	
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
	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());

}

void MapShopLevel::LevelEndEvent()
{

}

