#include "PreCompile.h"
#include "DirtmouthLevel1.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>

#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

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

	//GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	SetMapSize({ 3700, 3418 });

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 500, -0, static_cast<float>(Z_ORDER::Knight) });
	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


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

}

void DirtmouthLevel1::LevelEndEvent()
{


}
