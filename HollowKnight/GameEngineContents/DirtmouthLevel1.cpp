#include "PreCompile.h"
#include "DirtmouthLevel1.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>

#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"

DirtmouthLevel1::DirtmouthLevel1() 
{
}

DirtmouthLevel1::~DirtmouthLevel1() 
{
}

void DirtmouthLevel1::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}


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

	CreateUIActor();
	CreateMainCameraManager();
	CreateEffectGUIActor();
	CreateSettingPageActor();

	SetMapSize({ 3700, 3418 });

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 500, -0, static_cast<float>(Z_ORDER::Knight) });
	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();





}

void DirtmouthLevel1::Update(float _DeltaTime)
{

	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());

}

void DirtmouthLevel1::End()
{
}

void DirtmouthLevel1::LevelStartEvent()
{
	KnightData::GetInst()->SetCurrentLevel(GetNameConstRef());
	std::string EnumString;
	auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel4);
	EnumString = static_cast<std::string>(PrevName);

	std::string UpperName = GameEngineString::ToUpperReturn(EnumString);


	if (KnightData::GetInst()->GetPreLevel() == UpperName)
	{
		GetKnight()->GetTransform().SetLocalPosition({ 252, -973, static_cast<float>(Z_ORDER::Knight) });
		GetKnight()->SetDirInit(float4::LEFT);

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
