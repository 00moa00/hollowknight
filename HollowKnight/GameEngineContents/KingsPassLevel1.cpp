#include "PreCompile.h"
#include "KingsPassLevel1.h"
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

#include "KnightSoundManager.h"

#include "MapSmoke.h"



KingsPassLevel1::KingsPassLevel1() 
{
}

KingsPassLevel1::~KingsPassLevel1() 
{
}

void KingsPassLevel1::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_1.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_1.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_1.png");

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_1.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_1.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 928.f, -1503.f, static_cast<float>(Z_ORDER::Knight) });
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	
	SetMapSize({ 7099, 4889 });

	CreateUIActor();
	CreateSettingPageActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();
	//CreateMapSmokeMaker();

	//for (int i = 0; i < 130; ++i)
	//{
	//	MapSmoke* MapSmoke_= CreateActor<MapSmoke>();
	//	MapSmoke_->SetSpeed(0.f);
	//}


	{
		Potal* Potal_ = CreateActor<Potal>();

		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);

		Potal_->CreatePotal(UpperName, FadeMode::FadeOut);
		Potal_->GetTransform().SetWorldPosition({ 6895 + 60, -4639, });

	}


	{

		TutorialBreakDoor* TutorialBreakDoor_ = CreateActor<TutorialBreakDoor>();
		TutorialBreakDoor_->GetTransform().SetLocalPosition({ 2452, -4639, static_cast<float>(Z_ORDER::Object) });
	}

	{

		TutorialBreakDoor* TutorialBreakDoor_ = CreateActor<TutorialBreakDoor>();
		TutorialBreakDoor_->GetTransform().SetLocalPosition({ 3276, -4639, static_cast<float>(Z_ORDER::Object) });
	}

	{

		TutorialBreakDoor* TutorialBreakDoor_ = CreateActor<TutorialBreakDoor>();
		TutorialBreakDoor_->GetTransform().SetLocalPosition({ 4120, -4639, static_cast<float>(Z_ORDER::Object) });
	}

	{

		TutorialBreakDoor* TutorialBreakDoor_ = CreateActor<TutorialBreakDoor>();
		TutorialBreakDoor_->GetTransform().SetLocalPosition({ 5265, -4639 , static_cast<float>(Z_ORDER::Object) });
	}

	CreawteMapWhiteParticleMaker();

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);	
	

}
void KingsPassLevel1::Update(float _DeltaTime) 
{
	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());
}

void KingsPassLevel1::End() {}

void KingsPassLevel1::LevelStartEvent()
{

	KnightSoundManager::GetInst()->BgmOff();
	KnightSoundManager::GetInst()->BgmOn("cave_wind_loop.ogg", 300);


	CreateActor<FadeIn>();

	GetKnight()->SetDirInit(float4::RIGHT);

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel2);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 6895, -4639, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}

}

void KingsPassLevel1::LevelEndEvent()
{

}

