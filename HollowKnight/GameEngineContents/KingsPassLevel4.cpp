#include "PreCompile.h"
#include "KingsPassLevel4.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"


KingsPassLevel4::KingsPassLevel4() 
{
}

KingsPassLevel4::~KingsPassLevel4() 
{
}

void KingsPassLevel4::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_4.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_4.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_4.png");
	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_4.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_4.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();



	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 347.f, -1169.f, static_cast<float>(Z_ORDER::Knight) });
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 6210, 3271 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

}

void KingsPassLevel4::Update(float _DeltaTime)
{
}

void KingsPassLevel4::End()
{
}

void KingsPassLevel4::LevelStartEvent()
{

}

void KingsPassLevel4::LevelEndEvent()
{


}
