#include "PreCompile.h"
#include "KingsPassLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"


KingsPassLevel2::KingsPassLevel2() 
{
}

KingsPassLevel2::~KingsPassLevel2() 
{
}

void KingsPassLevel2::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_2.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_2.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_2.png");

	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어
	}

	CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_2.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_2.png");

	CreateUIActor();

	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 3888, 2546 });

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({614.f, -1764.f, static_cast<float>(Z_ORDER::Knight) });

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();


	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


}

void KingsPassLevel2::Update(float _DeltaTime)
{
}

void KingsPassLevel2::End()
{
}

void KingsPassLevel2::LevelStartEvent()
{

}

void KingsPassLevel2::LevelEndEvent()
{

}
