#include "PreCompile.h"
#include "LampBug.h"
#include <GameEngineBase\GameEngineRandom.h>

LampBug::LampBug() 
	:
	Dir_(),
	LimitMoveSize_(),
	PivotPos_(),

	Alpha_(1.0f),
	AlphaTImer_(0.f)
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
	
	float RamScale = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);

	GetRenderer()->GetTransform().SetWorldScale({ 105.f * RamScale, 105.f * RamScale });
	GetRenderer()->GetTransform().SetWorldPosition({ 0, 105.f * 3});

	GetRenderer()->ChangeFrameAnimation("FLY");

	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	Dir_.Normalize();

	AlphaTImer_ = GameEngineRandom::MainRandom.RandomFloat(3.0f, 6.0f);


	BugManager_.CreateStateMember("IDLE"
		, std::bind(&LampBug::LmapBugIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LampBug::LmapBugIdleStart, this, std::placeholders::_1)
		, std::bind(&LampBug::LmapBugIdleEnd, this, std::placeholders::_1));

	BugManager_.CreateStateMember("HIDE"
		, std::bind(&LampBug::LmapBugHideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&LampBug::LmapBugHideStart, this, std::placeholders::_1)
		, std::bind(&LampBug::LmapBugHideEnd, this, std::placeholders::_1));


	BugManager_.ChangeState("IDLE");

}

void LampBug::Update(float _DeltaTime)
{
	BugManager_.Update(_DeltaTime);
}

void LampBug::SetLimitMove(float4 _CurrentPos, float4 _LimitSize)
{
	PivotPos_ = _CurrentPos;

	PivotPos_.x += GameEngineRandom::MainRandom.RandomFloat(-30.0f, 30.0f);
	PivotPos_.y += GameEngineRandom::MainRandom.RandomFloat(-30.0f, 30.0f);

	LimitMoveSize_ = _LimitSize;
	GetTransform().SetWorldPosition({ PivotPos_.x , PivotPos_.y, static_cast<float>(Z_ORDER::Object)});
}

void LampBug::MovingBug()
{
	if (GetAccTime() > 5.0f)
	{
		Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		Dir_.Normalize();
		ReSetAccTime();
	}

	float4 Position{ };
	Position.x = GameEngineRandom::MainRandom.RandomFloat(0, 15.f);
	Position.y = GameEngineRandom::MainRandom.RandomFloat(0, 15.f);

	float4 CurrentPos = GetTransform().GetWorldPosition();
	float4 DestPos = GetTransform().GetWorldPosition() + (Position * Dir_);
	float4 Move = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 3.0f);

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

void LampBug::LmapBugIdleStart(const StateInfo& _Info)
{
	Alpha_ = 1.0f;

}

void LampBug::LmapBugIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MovingBug();

	if (AlphaTImer_ < _Info.StateTime)
	{
		Alpha_ -= 1.0f * _DeltaTime;

		if (Alpha_ <= 0.f)
		{
			Alpha_ = 0.f;
			GetRenderer()->GetPixelData().MulColor.a = 0.f;

			BugManager_.ChangeState("HIDE");
			return;
		}

		GetRenderer()->GetPixelData().MulColor.a = Alpha_;
	}
}

void LampBug::LmapBugIdleEnd(const StateInfo& _Info)
{
}

void LampBug::LmapBugHideStart(const StateInfo& _Info)
{
	Alpha_ = 0.f;
}

void LampBug::LmapBugHideUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MovingBug();

	if (_Info.StateTime > 1.0f)
	{
		Alpha_ += 1.0f * _DeltaTime;

		if (Alpha_ >= 1.f)
		{
			Alpha_ = 1.f;
			GetRenderer()->GetPixelData().MulColor.a = 1.0f;

			BugManager_.ChangeState("IDLE");
			return;
		}

		GetRenderer()->GetPixelData().MulColor.a = Alpha_;
	}
}

void LampBug::LmapBugHideEnd(const StateInfo& _Info)
{
	Alpha_ = 1.0f;
}

