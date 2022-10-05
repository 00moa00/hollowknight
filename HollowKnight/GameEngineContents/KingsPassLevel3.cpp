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
#include "BloomPostEffect.h"

#include "Potal.h"
#include "Tablet.h"

#include "AmblentLife.h"


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

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 4996.f + 60, -3309.f });

	}

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 3435.f + 60, -1169.f });

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2570.f , -2479.f }, 150);
		AmblentLife_->SetRamScale();

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2870.f , -2479.f }, 150);
		AmblentLife_->SetRamScale();

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2900.f , -2079.f }, 150);
		AmblentLife_->SetRamScale();

	}


	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 1800.f , -1900.f }, 150);
		AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 1700.f , -1200.f }, 150);
		AmblentLife_->SetRamScale();

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2000.f , -1364.f }, 150);
		AmblentLife_->SetRamScale();

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2100.f , -1064.f }, 200);
		AmblentLife_->SetRamScale();

	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2500.f , -964.f }, 200);
		AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 1514.f , -1400.f }, 200);
		AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 1700.f , -1600.f }, 200);
		AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2203.f , -2000.f }, 200);
		AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 3000.f , -2500.f }, 200);
		//AmblentLife_->SetRamScale();
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();

		AmblentLife_->SetLimitMove({ 2500.f , -1200.f }, 200);
		AmblentLife_->SetRamScale();
	}

	CreawteMapWhiteParticleMaker();


	Tablet* Tablet_ = CreateActor<Tablet>();
	Tablet_->CreateTablet("Mines_Layered_0017_a.png", "lit_tablet.png", {700, 500}, TabletType::FocusSpell);
	Tablet_->GetTransform().SetWorldPosition({ 4295,-3259, static_cast<float>(Z_ORDER::Back_Object)});
	Tablet_->GetTabletDialogue()->SetOnePage();

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();


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
	CreateActor<FadeIn>();


	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{

		GetKnight()->GetTransform().SetLocalPosition({ 4996.f, -3309.f, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}

	PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({3435.f, -1169.f, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}
}

void KingsPassLevel3::LevelEndEvent()
{

}
