#include "PreCompile.h"
#include "GrimmBird.h"

GrimmBird::GrimmBird()
	:
	MoveDir_(float4::ZERO),
	Speed_(0.f)
{
}

GrimmBird::~GrimmBird() 
{
}

void GrimmBird::Start()
{
	Speed_ = 400.f;
}

void GrimmBird::Update(float _DeltaTime)
{
	float4 Move = MoveDir_ * Speed_ * _DeltaTime;
	GetTransform().SetWorldMove(Move);
}

void GrimmBird::SetMoveDir(float4 _Dir)
{
	MoveDir_ = _Dir;
}