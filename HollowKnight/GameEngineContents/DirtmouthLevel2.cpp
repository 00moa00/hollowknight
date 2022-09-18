#include "PreCompile.h"
#include "DirtmouthLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "Bench.h"
#include "AreaTitle.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"
#include "BloomPostEffect.h"

DirtmouthLevel2::DirtmouthLevel2() 
	:
	Elderbug_(nullptr)
{
}

DirtmouthLevel2::~DirtmouthLevel2() 
{
}

void DirtmouthLevel2::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Dirtmouth_BackGround_2.png");
	GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_2.png");
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
	CreateMainCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 6646, 3418 });


	Bench* Test_ = CreateActor<Bench>();
	AreaTitle* AreaTitle_ = CreateActor<AreaTitle>();

	MapShopPotal_ = CreateActor<RoomPotal>();
	MapShopPotal_->CreatePotal(POTAL_TYPE::Map_Shop, true);
	MapShopPotal_->GetTransform().SetWorldPosition({3840, -3045.f });

	Elderbug_ = CreateActor<Elderbug>();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetWorldPosition({ 500.f, -2500.f, static_cast<float>(Z_ORDER::Knight) });
	
	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();
	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<BloomPostEffect>();

	//GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


}

void DirtmouthLevel2::Update(float _DeltaTime)
{
	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());

}

void DirtmouthLevel2::End()
{
}

void DirtmouthLevel2::LevelStartEvent()
{
	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel3);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -973, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

	}

	PrevName = magic_enum::enum_name(LevelList::DirtmouthLevel1);
	EnumString = static_cast<std::string>(PrevName);

	UpperName = GameEngineString::ToUpperReturn(EnumString);

	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -3127, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::RIGHT);

	}
}

void DirtmouthLevel2::LevelEndEvent()
{

}
