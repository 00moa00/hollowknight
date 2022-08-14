#include "PreCompile.h"
#include "KnightShadow.h"

KnightShadow::KnightShadow() 
{
}

KnightShadow::~KnightShadow() 
{
}

void KnightShadow::Start()
{
	CreateCollisionComponent(float4{ 60, 120, 1 }, static_cast<int>(OBJECTORDER::Knight_Shadow));
	GetCollision()->GetTransform().SetWorldPosition({ 0, 120 / 2, 0 });

}

void KnightShadow::Update(float _DeltaTime)
{
}

