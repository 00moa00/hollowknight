#include "PreCompile.h"
#include "CrossroadsLevel2.h"
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

CrossroadsLevel2::CrossroadsLevel2() 
{
}

CrossroadsLevel2::~CrossroadsLevel2() 
{
}

void CrossroadsLevel2::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Cross2_BackGround.png");
	GetMasterMap()->CreateBackGroundObject("Cross2_BackObject.png");
	GetMasterMap()->CreateMapCollision("Cross2_Coll.png");


	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어
	}

	CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("Cross2_Ground.png");
	GetMasterMap()->CreateFrontObject("Cross2_FrontObject.png");

	CreateUIActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 0, -0, 0 });

	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMainMapSize({ 5580, 1080 });

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();


}

void CrossroadsLevel2::Update(float _DeltaTime)
{
}

void CrossroadsLevel2::End()
{
}

void CrossroadsLevel2::LevelStartEvent()
{
	CreateActor<FadeIn>();

}

void CrossroadsLevel2::LevelEndEvent()
{

}
