#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>

Monster::Monster()
	:
	isMonsterDeath_(false),
	HitParticleCount_(0),
	HitParticlePuffCount_(0),
	HitLightCount_(0),
	DropGeo_(0),
	MonsterType_(MonsterType::Normal)

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

void Monster::SetDirRendererXScale()
{
	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	//	GetWallCollision()->GetTransform().SetLocalPosition({ -10, 50 });

	}

	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		//GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });

	}
}

void Monster::CreateMonsterDeathPuffParticle()
{
	MonsterDeathPuffParticle_ = GetLevel()->CreateActor<MonsterDeathPuffParticle>();
	MonsterDeathPuffParticle_->Off();
}

void Monster::SetMonsterDeathPuffParticleOn()
{
	MonsterDeathPuffParticle_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -50 });
	MonsterDeathPuffParticle_->ParticleOn();
}

