#include "PreCompile.h"
#include "AmblentLife.h"
#include <GameEngineBase\GameEngineRandom.h>

AmblentLife::AmblentLife() 
	:
	Dir_(),
	LimitMoveSize_(),
	PivotPos_()
{
}

AmblentLife::~AmblentLife() 
{
}

void AmblentLife::Start()
{
	CreateRendererComponent("Ambient Life_cave_glow_bug0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("FLY", FrameAnimation_DESC("Ambient Life_cave_glow_bug0000-Sheet.png", 0, 3, 0.100f, true));
	//GetRenderer()->SetScaleModeImage();
	GetRenderer()->GetTransform().SetLocalScale({184,181});
	GetRenderer()->ChangeFrameAnimation("FLY");
	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
}

void AmblentLife::Update(float _DeltaTime)
{
	if (GetAccTime() > 5.0f)
	{
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}


	float4 Position { };
	Position.x = GameEngineRandom::MainRandom.RandomFloat(0, 100);
	Position.y = GameEngineRandom::MainRandom.RandomFloat(0, 100);


	float4 CurrentPos = GetTransform().GetWorldPosition();
	float4 DestPos = GetTransform().GetWorldPosition() + (Position * Dir_);
	float4 Move = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 0.7f);

	GetTransform().SetWorldPosition(Move);

	if (GetTransform().GetWorldPosition().x <= PivotPos_.x - LimitMoveSize_.x )
	{
		float4 Position{ PivotPos_.x - LimitMoveSize_.x, GetTransform().GetWorldPosition().y };

		GetTransform().SetWorldPosition(Position);
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}

	if (GetTransform().GetWorldPosition().x >= PivotPos_.x + LimitMoveSize_.x)
	{
		float4 Position{ PivotPos_.x + LimitMoveSize_.x, GetTransform().GetWorldPosition().y };

		GetTransform().SetWorldPosition(Position);
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}

	if (GetTransform().GetWorldPosition().y >= PivotPos_.y + LimitMoveSize_.y)
	{
		float4 Position{ GetTransform().GetWorldPosition().x,  PivotPos_.y + LimitMoveSize_.y };

		GetTransform().SetWorldPosition(Position);
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();

	}

	if (GetTransform().GetWorldPosition().y <= PivotPos_.y - LimitMoveSize_.y)
	{
		float4 Position{ GetTransform().GetWorldPosition().x,  PivotPos_.y - LimitMoveSize_.y };

		GetTransform().SetWorldPosition(Position);
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}
}

void AmblentLife::SetLimitMove(float4 _CurrentPos, float4 _LimitSize)
{
	PivotPos_ = _CurrentPos;
	LimitMoveSize_ = _LimitSize;
	GetTransform().SetWorldPosition({ _CurrentPos.x ,_CurrentPos.y, static_cast<float>(Z_ORDER::Object) });
}

void AmblentLife::SetRamScale()
{
	float RamScale = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f);

	GetRenderer()->GetTransform().SetLocalScale({ 184 * RamScale, 181* RamScale });

}

