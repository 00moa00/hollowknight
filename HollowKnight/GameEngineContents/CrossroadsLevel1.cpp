#include "PreCompile.h"
#include "CrossroadsLevel1.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

CrossroadsLevel1::CrossroadsLevel1() 
{
}

CrossroadsLevel1::~CrossroadsLevel1() 
{
}

void CrossroadsLevel1::Start()
{

	CraateMasterMapActor();

	//GetMasterMap()->CreateBackGround("Cross1_BackGround.png");
	//GetMasterMap()->CreateBackGroundObject("Cross1_BackObject.png");
	GetMasterMap()->CreateMapCollision("Cross1_Coll.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	//GetMasterMap()->CreateTerrain("Cross1_Ground.png");
	//GetMasterMap()->CreateFrontObject("Cross1_FrontObject.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMainMapSize({ 6633, 1661 });

	GetKnight()->GetTransform().SetLocalPosition({ 0, -0, 0 });

}

void CrossroadsLevel1::Update(float _DeltaTime)
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	CameraMoveWindowLimit();
}

void CrossroadsLevel1::End()
{
}
