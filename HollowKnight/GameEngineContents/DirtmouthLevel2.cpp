#include "PreCompile.h"
#include "DirtmouthLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "Bench.h"
#include "AreaTitle.h"

DirtmouthLevel2::DirtmouthLevel2() 
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
	//CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("Dirtmouth_Terrian_2.png");
	GetMasterMap()->CreateFrontObject("Dirtmouth_MapObject_2.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	//GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();

	SetMainMapSize({ 6646, 3418 });

	GetKnight()->GetTransform().SetLocalPosition({ 500.f, -2500.f, static_cast<float>(Z_ORDER::Knight) });

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	Bench* Test_ = CreateActor<Bench>();

	AreaTitle* AreaTitle_ = CreateActor<AreaTitle>();
}

void DirtmouthLevel2::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	CameraMoveWindowLimit();
}

void DirtmouthLevel2::End()
{
}
