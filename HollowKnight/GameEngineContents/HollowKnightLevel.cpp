#include "PreCompile.h"
#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
HollowKnightLevel::HollowKnightLevel() 
	:
	MasterMap_(nullptr),
	Knight_(nullptr)
{
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::CraateMasterMapActor()
{
	MasterMap_ = CreateActor<MasterMap>();

}

void HollowKnightLevel::CreateKnightActor()
{
	Knight_ = CreateActor<Knight>();

}

