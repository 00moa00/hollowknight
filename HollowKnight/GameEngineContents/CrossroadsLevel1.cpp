#include "PreCompile.h"
#include "CrossroadsLevel1.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "Potal.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"


CrossroadsLevel1::CrossroadsLevel1() 
{
}

CrossroadsLevel1::~CrossroadsLevel1() 
{
}

void CrossroadsLevel1::Start()
{

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Cross1_BackGround.png");
	GetMasterMap()->CreateBackGroundObject("Cross1_BackObject.png");
	GetMasterMap()->CreateMapCollision("Cross1_Coll.png");


	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어
	}


	CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("Cross1_Ground.png");
	GetMasterMap()->CreateFrontObject("Cross1_FrontObject.png");

	CreateUIActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();


	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 6633, 1661 });

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 0, -0, static_cast<float>(Z_ORDER::Knight) });

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
}

void CrossroadsLevel1::Update(float _DeltaTime)
{
	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());

}

void CrossroadsLevel1::End()
{
}

void CrossroadsLevel1::LevelStartEvent()
{
	CreateActor<FadeIn>();


}

void CrossroadsLevel1::LevelEndEvent()
{

}
