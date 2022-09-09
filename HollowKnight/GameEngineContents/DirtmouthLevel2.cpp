#include "PreCompile.h"
#include "DirtmouthLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"
#include "OverlayPostEffect.h"

#include "Bench.h"
#include "AreaTitle.h"
#include "OverlayBlend.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"

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

	CreateKnightActor(); // 플레이어

	GetMasterMap()->CreateTerrain("Dirtmouth_Terrian_2.png");
	GetMasterMap()->CreateFrontObject("Dirtmouth_MapObject_2.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();

	SetMainMapSize({ 6646, 3418 });

	GetKnight()->GetTransform().SetLocalPosition({ 500.f, -2500.f, static_cast<float>(Z_ORDER::Knight) });

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	Bench* Test_ = CreateActor<Bench>();
	AreaTitle* AreaTitle_ = CreateActor<AreaTitle>();

	MapShopPotal_ = CreateActor<RoomPotal>();
	MapShopPotal_->CreatePotal(POTAL_TYPE::Map_Shop, true);
	MapShopPotal_->GetTransform().SetWorldPosition({3840, -3045.f });


	Elderbug_ = CreateActor<Elderbug>();


	//OverlayBlend* OverlayBlend_;
	//OverlayBlend_ = CreateActor<OverlayBlend>();
	//GameEngineDevice::GetBackBuffer()->AddEffect<OverlayPostEffect>();

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();

	//GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();


	

	//std::list<GameEnginePostEffect*> FindEffect = GetMainCamera()->GetCameraRenderTarget()->Effects;
	

//	GetMainCamera()->GetCameraRenderTarget()->
	//GameEngineTexture* GameEngineTexture_;
	//GameEngineTexture_ = GameEngineTexture::Find("PostEffectOverlay.png");

}

void DirtmouthLevel2::Update(float _DeltaTime)
{
	CameraMoveWindowLimit();
	//std::list<GameEnginePostEffect*> Find = GetMainCamera()->GetCameraRenderTarget()->Effects;

	//for (GameEnginePostEffect* Effect : Find)
	//{
	//	Effect->Update(_DeltaTime);
	//}
}

void DirtmouthLevel2::End()
{
}
