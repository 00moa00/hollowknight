#include "PreCompile.h"
#include "KingsPassGrimmOpenLevel.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "Potal.h"

#include "TutorialBreakDoor.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "MapSmoke.h"
#include "Sycophant.h"

#include "GrimmCastPillarEffect.h"

#include "GrimmFlameEffect.h"
#include "GrimmFlameParticle.h"


KingsPassGrimmOpenLevel::KingsPassGrimmOpenLevel() 
{
}

KingsPassGrimmOpenLevel::~KingsPassGrimmOpenLevel() 
{
}

void KingsPassGrimmOpenLevel::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("GrimmOpen_BackGround.png");
	GetMasterMap()->CreateBackGroundObject("GrimmOpen_BackGroundObject_1.png");
	GetMasterMap()->CreateMapCollision("GrimmOpen_CollMap.png");

	GetMasterMap()->CreateTerrain("GrimmOpen_Terrain.png");
	GetMasterMap()->CreateFrontObject("GrimmOpen_Object.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 200.f, -1003.f, static_cast<float>(Z_ORDER::Knight) });
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 6124, 1080 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 200.f - 60, -936.f, });
	}

	{
		Sycophant* Sycophant_ = CreateActor<Sycophant>();
	}

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 290.f, -600.f, 41 });
	}

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 2190.f, -600.f , 41 });
	}

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 4210.f, -600.f , 41 });
	}

	{
		GrimmFlameParticle* GrimmFlameParticle_ = CreateActor<GrimmFlameParticle>();
		GrimmFlameParticle_->GetTransform().SetWorldPosition({ 2507.f, -300.f , 41 });
	}


	CreawteMapWhiteParticleMaker();

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

}

void KingsPassGrimmOpenLevel::Update(float _DeltaTime)
{
}

void KingsPassGrimmOpenLevel::End()
{
}

void KingsPassGrimmOpenLevel::LevelStartEvent()
{
	CreateActor<FadeIn>();

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());

	GetKnight()->GetTransform().SetLocalPosition({ 200.f, -936.f, static_cast<float>(Z_ORDER::Knight) });
	GetKnight()->SetDirInit(float4::RIGHT);
}

void KingsPassGrimmOpenLevel::LevelEndEvent()
{
}
