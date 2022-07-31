#include "PreCompile.h"
#include "KingsPassLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"

KingsPassLevel::KingsPassLevel() 
{
}

KingsPassLevel::~KingsPassLevel() 
{
}

void KingsPassLevel::Start()
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

	//GetMasterMap()->CreateBackGround("King's-Pass_Background_1.png");
	//GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_1.png");
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_1.png");


	CreateKnightActor(); // 플레이어
	//GetMasterMap()->CreateTerrain("King's-Pass_Terrain_1.png");
	GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_1.png");

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	SetMainMapSize({7099, 4889});


}
void KingsPassLevel::Update(float _DeltaTime) 
{
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		// ;
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	CameraMoveWindowLimit();
}

void KingsPassLevel::End() {}

