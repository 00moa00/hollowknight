#include "PreCompile.h"
#include "AllLocalMap.h"
#include "HollowKnightLevel.h"

AllLocalMap::AllLocalMap() 
{
}

AllLocalMap::~AllLocalMap() 
{
}

void AllLocalMap::Start()
{
	//GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->GetTransform().SetWorldRotation({0, -100.f});
}

void AllLocalMap::Update(float _DeltaTime)
{
}

void AllLocalMap::OpenAllLocalMap()
{
	GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->On();
}

void AllLocalMap::CloseAllLocalMap()
{
	GetLevel<HollowKnightLevel>()->GetForgottenCrossroadMap()->Off();
}

