#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::SetMonsterDirection()
{
	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });

	}

	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });

	}

}

