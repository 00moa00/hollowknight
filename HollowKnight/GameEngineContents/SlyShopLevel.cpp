#include "PreCompile.h"
#include "SlyShopLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "RoomPotal.h"
#include "BloomPostEffect.h"

#include "ShopLampBug.h"


SlyShopLevel::SlyShopLevel() 
{
}

SlyShopLevel::~SlyShopLevel() 
{
}

void SlyShopLevel::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("SlyShop_Background.png");
	GetMasterMap()->CreateMapCollision("SlyShop_Coll.png");

	CreateKnightActor(); // 플레이어

	GetMasterMap()->CreateTerrain("SlyShop_Terrian.png");
	GetMasterMap()->CreateFrontObject("SlyShop_FrontObject.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();
	CreateMainCameraManager();
	CreateEffectGUIActor();
	CreateHeartPiece();

	CreateSly();

	RoomPotal* DirtmouthPotal_ = CreateActor<RoomPotal>();
	DirtmouthPotal_->CreatePotal(POTAL_TYPE::Dirt, false);
	DirtmouthPotal_->GetTransform().SetWorldPosition({ 400, -870.f });

	{
		ShopLampBug* ShopLampBug_ = CreateActor<ShopLampBug>();
		ShopLampBug_->GetTransform().SetWorldPosition({1075, -590.f});

	}

	SetMapSize({ 1920, 1080 });

	GetKnight()->GetTransform().SetLocalPosition({ 800, 0.f, static_cast<float>(Z_ORDER::Knight) });
	
	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

}

void SlyShopLevel::Update(float _DeltaTime)
{
	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());

}

void SlyShopLevel::End()
{
}

void SlyShopLevel::LevelStartEvent()
{
	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());

}

void SlyShopLevel::LevelEndEvent()
{

}

