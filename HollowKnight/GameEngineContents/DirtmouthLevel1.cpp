#include "PreCompile.h"
#include "DirtmouthLevel1.h"
#include <GameEngineCore/GameEngineCameraActor.h>

#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "Potal.h"

#include "BloomPostEffect.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "Potal.h"

#include "MapWhiteParticleWindMaker.h"

DirtmouthLevel1::DirtmouthLevel1() 
{
}

DirtmouthLevel1::~DirtmouthLevel1() 
{
}

void DirtmouthLevel1::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Dirtmouth_BackGround_1.png");
	GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_1.png");
	GetMasterMap()->CreateMapCollision("Dirtmouth_1_Coll.png");

	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어

	}	//CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("Dirtmouth_Terrian_1.png");
	GetMasterMap()->CreateFrontObject("Dirtmouth_MapObject_1.png");

	SetMapSize({ 3700, 3418 });

	CreateUIActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();
	CreateSettingPageActor();


	{
		Potal* KingsPassLevel4Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		KingsPassLevel4Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		KingsPassLevel4Potal_->GetTransform().SetWorldPosition({ 252 - 60, -973 });

	}

	{
		Potal* DirtmouthLevel2Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel2);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		DirtmouthLevel2Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		DirtmouthLevel2Potal_->GetTransform().SetWorldPosition({ 3492 + 60, -3119 });

	}


	CreateMapSmokeMaker();
	CreateActor<MapWhiteParticleWindMaker>();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 500, -0, static_cast<float>(Z_ORDER::Knight) });
	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

}

void DirtmouthLevel1::Update(float _DeltaTime)
{

}

void DirtmouthLevel1::End()
{
}

void DirtmouthLevel1::LevelStartEvent()
{
	GetKnight()->GetTransform().SetLocalPosition({ 252, -973, static_cast<float>(Z_ORDER::Knight) });
	GetKnight()->SetDirInit(float4::RIGHT);
	CreateActor<FadeIn>();

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -973, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::RIGHT);

	}

	 PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel2);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 3492, -3119, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}

}

void DirtmouthLevel1::LevelEndEvent()
{



}
