#include "PreCompile.h"
#include "KingsPassLevel3.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"


KingsPassLevel3::KingsPassLevel3() 
{
}

KingsPassLevel3::~KingsPassLevel3() 
{
}

void KingsPassLevel3::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_3.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_3.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_3.png");

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_3.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_3.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 4996.f, -3309.f, static_cast<float>(Z_ORDER::Knight) });
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	
	SetMapSize({ 5183, 3947 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();


	//GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


}

void KingsPassLevel3::Update(float _DeltaTime)
{
}

void KingsPassLevel3::End()
{
}

void KingsPassLevel3::LevelStartEvent()
{

}

void KingsPassLevel3::LevelEndEvent()
{

}
