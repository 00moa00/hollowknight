#include "PreCompile.h"
#include "KingsPassLevel2.h"
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
#include "BloomPostEffect.h"

#include "AmblentLife.h"

#include "Buzzer.h"


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

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_2.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_2.png");

	CreateKnightActor(); // �÷��̾�
	CreateKingsPass2Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 509.f, -1826.f, static_cast<float>(Z_ORDER::Knight) });
	
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 3888, 2546 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();


	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel1);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 209.f - 60.f, -1826.f });
	}

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel3);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 172.f - 60, -532.f, });
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();
		AmblentLife_->SetLimitMove({ 1217.f , -2000.f }, 150);
	}

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();
		AmblentLife_->SetLimitMove({ 1607.f , -1600.f }, 150);
	} 

	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();
		AmblentLife_->SetLimitMove({ 1317.f , -1300.f }, 150);
	}


	{
		AmblentLife* AmblentLife_ = CreateActor<AmblentLife>();
		AmblentLife_->SetLimitMove({ 1817.f , -1000.f }, 150);
	}

	Buzzer* Buzzer_ = CreateActor<Buzzer>();
	Buzzer_->GetTransform().SetWorldPosition({1852, -1296});
	Buzzer_->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreawteMapWhiteParticleMaker();

	PustItemInventroy(ITEM_LIST::Shade_Cloak);
	PustItemInventroy(ITEM_LIST::Mantis_Cloak);

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

}

void KingsPassLevel2::Update(float _DeltaTime)
{
}

void KingsPassLevel2::End()
{
}

void KingsPassLevel2::LevelStartEvent()
{
	CreateActor<FadeIn>();

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel1);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 209.f, -1826.f, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::RIGHT);

	}

	PrevName = magic_enum::enum_name(LevelList::KingsPassLevel3);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 172.f, -532.f, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}


}

void KingsPassLevel2::LevelEndEvent()
{

}
