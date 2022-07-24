#include "PreCompile.h"
#include "KingsPassLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Knight.h"
#include "Monster.h"

KingsPassLevel::KingsPassLevel() 
	:
	MasterMap_(nullptr),
	Knight_(nullptr)
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


	MasterMap_ = CreateActor<MasterMap>();
	MasterMap_->CreateBackGround("King's-Pass_Background_", float4{1859,1774}, 6, 3);
	MasterMap_->CreateBackGroundObject("King's-Pass_Background_Object_", float4{ 1859,1774 }, 6, 3);
	Knight_ = CreateActor<Knight>();
	MasterMap_->CreateTerrain("King's-Pass_Terrain_", float4{ 1859,1774 }, 6, 3);
	MasterMap_->CreateFrontObject("King's-Pass_FrontObject_", float4{ 1859,1774 }, 6, 3);
	


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
