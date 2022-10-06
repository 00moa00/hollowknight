#include "PreCompile.h"
#include "GrimmDirtmouthLevel3.h"

#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "Potal.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "BloomPostEffect.h"


GrimmDirtmouthLevel3::GrimmDirtmouthLevel3() 
{
}

GrimmDirtmouthLevel3::~GrimmDirtmouthLevel3() 
{
}

void GrimmDirtmouthLevel3::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_3.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_3.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_3.png");

	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어
	}

	CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_3.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_3.png");

	CreateUIActor();

	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 5183, 3947 });

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ -1330.f, -490.f, static_cast<float>(Z_ORDER::Knight) });

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

}

void GrimmDirtmouthLevel3::Update(float _DeltaTime)
{
}

void GrimmDirtmouthLevel3::End()
{
}

void GrimmDirtmouthLevel3::LevelStartEvent()
{
}

void GrimmDirtmouthLevel3::LevelEndEvent()
{
}
