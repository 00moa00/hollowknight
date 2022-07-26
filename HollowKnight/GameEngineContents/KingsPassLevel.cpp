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
	//if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	//{
	//	GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	//}

	{
		GameEngineCameraActor* actor = CreateActor<GameEngineCameraActor>();
		actor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
		actor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -500.0f });

	}

	CraateMasterMapActor();
	GetMasterMap()->CreateBackGround("King's-Pass_Background_", float4{1859,1774}, 6, 3);
	GetMasterMap()->CreateBackGroundObject("King's-Pass_Background_Object_", float4{ 1859,1774 }, 6, 3);
	GetMasterMap()->CreateMapCollision("King's-Pass_CollMap_", float4{ 1859,1774 }, 6, 3);

	CreateKnightActor();
	GetKnight()->InsertMapCollisionTexture(GetMasterMap()->GetCollisionMap());

	//GetMasterMap()->CreateTerrain("King's-Pass_Terrain_", float4{ 1859,1774 }, 6, 3);
	//GetMasterMap()->CreateFrontObject("King's-Pass_FrontObject_", float4{ 1859,1774 }, 6, 3);


}
void KingsPassLevel::Update(float _DeltaTime) 
{
	//if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	//{
	//	// ;
	//	GetMainCameraActor()->FreeCameraModeOnOff();
	//}
}

void KingsPassLevel::End() {}
