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
#include "BloomPostEffect.h"

#include "GrimmLantern.h"

#include "Brummm.h"



GrimmLevel::GrimmLevel() 
	:
	Grimm_(nullptr),
	GrimmCrowds_(nullptr)
{
}

GrimmLevel::~GrimmLevel() 
{
}

void GrimmLevel::Start()
{



	if (false == GameEngineInput::GetInst()->IsKey("CamMoveForward"))
	{
		GameEngineInput::GetInst()->CreateKey("CamMoveForward", 'W');
		GameEngineInput::GetInst()->CreateKey("CamMoveBack", 'S');
		GameEngineInput::GetInst()->CreateKey("CamMoveUp", 'Q');
		GameEngineInput::GetInst()->CreateKey("CamMoveDown", 'E');
		GameEngineInput::GetInst()->CreateKey("CamMoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("CamMoveRight", 'D');

		GameEngineInput::GetInst()->CreateKey("CamMoveBoost", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("CamRot", VK_RBUTTON);
	}

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Grimm_Background.png");
	GetMasterMap()->CreateBackGroundObject("Grimm_Background_Object.png");
	GetMasterMap()->CreateMapCollision("Grimm_Coll.png");

	GetMasterMap()->CreateTerrain("Grimm_Terrian.png");
	GetMasterMap()->CreateFrontObject("Grimm_FrontObject.png");

	CreateKnightActor(); // 플레이어
	//CreateKingsPass1Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 100, -500.f, static_cast<float>(Z_ORDER::Knight) });
	//GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMapSize({ 6092, 1079 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	Grimm_ = CreateActor<Grimm>();
	Grimm_->GetTransform().SetWorldPosition({5380,-900 , static_cast<float>(Z_ORDER::Monster) });
	Grimm_->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	GrimmCrowds_ = CreateActor<GrimmCrowds>();
	GrimmCrowds_->Off();

	CreateActor<Brummm>();
	{
		GrimmLantern* GrimmLantern_ = CreateActor<GrimmLantern>();
		GrimmLantern_->GetTransform().SetWorldPosition({ 4430, -100 });
	}

	{
		GrimmLantern* GrimmLantern_ = CreateActor<GrimmLantern>();
		GrimmLantern_->GetTransform().SetWorldPosition({ 4100, -200 });
	}

	{
		GrimmLantern* GrimmLantern_ = CreateActor<GrimmLantern>();
		GrimmLantern_->GetTransform().SetWorldPosition({ 5200, -250 });
	}

	//{
	//	GrimmCrowd* GrimmCrowd_ = CreateActor<GrimmCrowd>();
	//	GrimmCrowd_->GetTransform().SetWorldPosition({ 5500,-400 , static_cast<float>(Z_ORDER::Back_Back_Object) });
	//}



	//{
	//	Potal* Potal_ = CreateActor<Potal>();

	//	std::string EnumString;
	//	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
	//	EnumString = static_cast<std::string>(PrevName);

	//	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

	//	Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
	//	Potal_->GetTransform().SetWorldPosition({ 6895 + 60, -4639, });

	//}

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);


	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);	
	
	
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();
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
