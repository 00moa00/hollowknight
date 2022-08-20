#include "PreCompile.h"
#include "KingsPassLevel1.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

KingsPassLevel1::KingsPassLevel1() 
{
}

KingsPassLevel1::~KingsPassLevel1() 
{
}

void KingsPassLevel1::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}

	/*{
		GameEngineCameraActor* actor = CreateActor<GameEngineCameraActor>();
		actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	}*/

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("King's-Pass_Background_1.png");
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_1.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_1.png");

	CreateKnightActor(); // 플레이어
	CreateKingsPass1Monster();

	GetMasterMap()->CreateTerrain("King's-Pass_Terrain_1.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_1.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetCrawlid()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();

	SetMainMapSize({7099, 4889});
	//GetMainCameraActor()->GetCameraComponent()->GetTransform().SetWorldPosition();
	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
}
void KingsPassLevel1::Update(float _DeltaTime) 
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	CameraMoveWindowLimit();
}

void KingsPassLevel1::End() {}

