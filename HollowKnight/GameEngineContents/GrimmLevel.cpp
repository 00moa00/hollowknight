#include "PreCompile.h"


#include "GrimmLevel.h"
#include "GlobalContentsValue.h"
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

GrimmLevel::GrimmLevel() 
	:
	Grimm_(nullptr)
{
}

GrimmLevel::~GrimmLevel() 
{
}

void GrimmLevel::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Grimm_Background.png");
	GetMasterMap()->CreateBackGroundObject("Grimm_Background_Object.png");
	GetMasterMap()->CreateMapCollision("Grimm_Coll.png");

	GetMasterMap()->CreateTerrain("Grimm_Terrian.png");
	GetMasterMap()->CreateFrontObject("Grimm_FrontObject.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 100, -500.f, static_cast<float>(Z_ORDER::Knight) });
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 6092, 1079 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	Grimm_ = CreateActor<Grimm>();
	Grimm_->GetTransform().SetWorldPosition({5380,-950 , static_cast<float>(Z_ORDER::Monster) });


	//{
	//	Potal* Potal_ = CreateActor<Potal>();

	//	std::string EnumString;
	//	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
	//	EnumString = static_cast<std::string>(PrevName);

	//	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

	//	Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
	//	Potal_->GetTransform().SetWorldPosition({ 6895 + 60, -4639, });

	//}



	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();
}

void GrimmLevel::Update(float _DeltaTime)
{
}

void GrimmLevel::End()
{
}

void GrimmLevel::LevelStartEvent()
{
	CreateActor<FadeIn>();

	GetKnight()->SetDirInit(float4::RIGHT);

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel2);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 100, -500, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}
}

void GrimmLevel::LevelEndEvent()
{
}
