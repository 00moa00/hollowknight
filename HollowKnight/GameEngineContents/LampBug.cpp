#include "PreCompile.h"
#include "LampBug.h"
#include <GameEngineBase\GameEngineRandom.h>

LampBug::LampBug() 
	:
	Dir_(),
	LimitMoveSize_(),
	PivotPos_(),

	Alpha_(1.0f)
{
}

LampBug::~LampBug() 
{
}

void LampBug::Start()
{
	CreateRendererComponent("shop_lamp_bug0000-Sheet.png");

	GetRenderer()->CreateFrameAnimationCutTexture("FLY", FrameAnimation_DESC("shop_lamp_bug0000-Sheet.png", 0, 7, 0.100f, true));
	GetRenderer()->SetScaleModeImage();

	GetRenderer()->ChangeFrameAnimation("FLY");

	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir_.Normalize();

}

void LampBug::Update(float _DeltaTime)
{
	if (GetAccTime() > 5.0f)
	{
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.Normalize();
		ReSetAccTime();
	}

	float4 Position{ };
	Position.x = GameEngineRandom::MainRandom.RandomFloat(0, 10.f);
	Position.y = GameEngineRandom::MainRandom.RandomFloat(0, 10.f);

	float4 CurrentPos = GetTransform().GetWorldPosition();
	float4 DestPos = GetTransform().GetWorldPosition() + (Position * Dir_);
	float4 Move = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 0.7f);

	GetTransform().SetWorldPosition(Move);

	if (GetTransform().GetWorldPosition().x <= PivotPos_.x - LimitMoveSize_.x)
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

void LampBug::SetLimitMove(float4 _CurrentPos, float4 _LimitSize)
{
	PivotPos_ = _CurrentPos;
	LimitMoveSize_ = _LimitSize;
	GetTransform().SetWorldPosition({_CurrentPos.x , _CurrentPos.y, static_cast<float>(Z_ORDER::Object)});
}

