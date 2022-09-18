#include "PreCompile.h"
#include "KingsPassLevel4.h"
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

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel3);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 3492.f - 60, -3119.f });

	}

	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel1);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 5891.f + 60, -1169.f });

	}

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

	CreateActor<FadeIn>();

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel3);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 3492.f, -3119.f, static_cast<float>(Z_ORDER::Knight) });

	}

	PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel1);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 5891.f, -1169.f, static_cast<float>(Z_ORDER::Knight) });


	}
}

void KingsPassLevel4::LevelEndEvent()
{


}
