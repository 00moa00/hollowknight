#include "PreCompile.h"
#include "SlyShopLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

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
	//GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_2.png");
	GetMasterMap()->CreateMapCollision("SlyShop_Coll.png");

	CreateKnightActor(); // 플레이어

	GetMasterMap()->CreateTerrain("SlyShop_Terrian.png");
	GetMasterMap()->CreateFrontObject("SlyShop_FrontObject.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();

	SetMainMapSize({ 1920, 1080 });

	GetKnight()->GetTransform().SetLocalPosition({ 800, 0.f, static_cast<float>(Z_ORDER::Knight) });

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
}

void SlyShopLevel::Update(float _DeltaTime)
{
	CameraMoveWindowLimit();

}

void SlyShopLevel::End()
{
}

