#include "PreCompile.h"
#include "GrimmDirtmouthLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "Bench.h"
#include "AreaTitle.h"
#include "Potal.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "BloomPostEffect.h"
#include "GrimmFlameEffect.h"

#include "LampBugGrow.h"
#include "LampBug.h"

#include "MapWhiteParticleWindMaker.h"


GrimmDirtmouthLevel2::GrimmDirtmouthLevel2() 
	:
	Elderbug_(nullptr)
{
}

GrimmDirtmouthLevel2::~GrimmDirtmouthLevel2() 
{
}

void GrimmDirtmouthLevel2::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Dirtmouth_BackGround_2.png");
	GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_GrimmBoss_2.png");
	GetMasterMap()->CreateMapCollision("Dirtmouth_2_Coll.png");

	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // 플레이어
	}

	GetMasterMap()->CreateTerrain("Dirtmouth_Terrian_2.png");
	GetMasterMap()->CreateFrontObject("Dirtmouth_MapObject_2.png");

	CreateUIActor();

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();
	CreateDirtmouthMap();

	CreateAllLocalMap();
	CreateMainCameraManager();
	CreateMapCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 6646, 3418 });


	Bench* Test_ = CreateActor<Bench>();
	AreaTitle* AreaTitle_ = CreateActor<AreaTitle>();

	SlyShopPotal_ = CreateActor<RoomPotal>();
	SlyShopPotal_->CreatePotal(POTAL_TYPE::Sly_Shop, true);
	SlyShopPotal_->GetTransform().SetWorldPosition({ 3840, -3045.f });

	MapShopPotal_ = CreateActor<RoomPotal>();
	MapShopPotal_->CreatePotal(POTAL_TYPE::Map_Shop, true);
	MapShopPotal_->GetTransform().SetWorldPosition({ 6008, -3127.f });


	Elderbug_ = CreateActor<Elderbug>();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetWorldPosition({ 500.f, -2500.f, static_cast<float>(Z_ORDER::Knight) });

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 285.f, -2587.f , 41 });
	}

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 2700.f, -2587.f , 41 });
	}

	{
		GrimmFlameEffect* GrimmFlameEffect_ = CreateActor<GrimmFlameEffect>();
		GrimmFlameEffect_->GetTransform().SetWorldPosition({ 4192.f, -2587.f , 41 });
	}



	{
		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 414.f, -3010.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 414.f, -3010.f }, { 10,10 });
		}

		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 414.f + 221.f, -2880.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 414.f + 221.f, -2880.f }, { 10,10 });
		}
	}

	{
		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 2181.f, -3010.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 2181.f, -3010.f }, { 10,10 });
		}

		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 2181.f + 221.f, -2880.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 2181.f + 221.f, -2880.f }, { 10,10 });
		}
	}


	{
		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 4338.f, -3010.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 4338.f, -3010.f }, { 10,10 });
		}

		{
			LampBugGrow* LampBugGrow_ = CreateActor<LampBugGrow>();
			LampBugGrow_->GetTransform().SetWorldPosition({ 4338.f + 221.f, -2880.f });
		}

		for (int i = 0; i < 3; ++i)
		{
			LampBug* LampBug_ = CreateActor<LampBug>();
			LampBug_->SetLimitMove({ 4338.f + 221.f, -2880.f }, { 10,10 });
		}
	}

	//BloomPostEffect* BloomPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();
	//BloomPostEffect_->SetHollowKnightLevel(this);

	CreateMapSmokeMaker();
	CreateActor<MapWhiteParticleWindMaker>();

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	NoisePostEffect* NoisePostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	NoisePostEffect_->SetHollowKnightLevel(this);

}

void GrimmDirtmouthLevel2::Update(float _DeltaTime)
{
}

void GrimmDirtmouthLevel2::End()
{
}

void GrimmDirtmouthLevel2::LevelStartEvent()
{
	CreateActor<FadeIn>();

	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());

	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::GrimmDirtmouthLevel3);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -973, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);
	}

	PrevName = magic_enum::enum_name(LevelList::GrimmDirtmouthLevel1);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -3127, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::RIGHT);
	}


}

void GrimmDirtmouthLevel2::LevelEndEvent()
{
}
