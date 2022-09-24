#include "PreCompile.h"
#include "GrimmStunBat.h"
#include <GameEngineBase\GameEngineRandom.h>
GrimmStunBat::GrimmStunBat() 
	:
	isMoveGrimm_(false),
	Speed_(0.f),
	MoveDir_(float4::ZERO),
	GrimmBirdStateManager()
{
}

GrimmStunBat::~GrimmStunBat() 
{
}

void GrimmStunBat::Start()
{
	Speed_ = 300.f;

//	CreateCollisionComponent({ 30,1500 }, static_cast<int>(COLLISION_ORDER::Monster_Attack));

	CreateRendererComponent("Grimm Cln_Grimm_stun_bat0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("APPEAR_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_stun_bat0000-Sheet.png", 0, 1, 0.060f, false));
	GetRenderer()->ScaleToCutTexture(0);

	std::vector<unsigned int> CustomAni;

	CustomAni.push_back(1);
	CustomAni.push_back(2);
	CustomAni.push_back(3);
	CustomAni.push_back(5);
	CustomAni.push_back(6);


	GetRenderer()->CreateFrameAnimationCutTexture("FLY_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_stun_bat0000-Sheet.png", CustomAni, 0.060f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Grimm Cln_Grimm_stun_bat0000-Sheet.png", 7, 8, 0.060f, true));


	GetRenderer()->ChangeFrameAnimation("FLY_ANIMATION");

	GetRenderer()->AnimationBindEnd("APPEAR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{

			GetRenderer()->ChangeFrameAnimation("FLY_ANIMATION");

		});


	GrimmBirdStateManager.CreateStateMember("FLY"
		, std::bind(&GrimmStunBat::BatFlyUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmStunBat::BatFlyStart, this, std::placeholders::_1)
		, std::bind(&GrimmStunBat::BatFlyEnd, this, std::placeholders::_1));

	GrimmBirdStateManager.CreateStateMember("MOVE_TO_GRIMM"
		, std::bind(&GrimmStunBat::BatMoveToGrimmUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmStunBat::BatMoveToGrimmStart, this, std::placeholders::_1)
		, std::bind(&GrimmStunBat::BatMoveToGrimmEnd, this, std::placeholders::_1));

	GrimmBirdStateManager.ChangeState("FLY");

	MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
	MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
}

void GrimmStunBat::Update(float _DeltaTime)
{
	GrimmBirdStateManager.Update(_DeltaTime);
}


void GrimmStunBat::BatFlyStart(const StateInfo& _Info)
{
}

void GrimmStunBat::BatFlyUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetAccTime() > 5.0f)
	{

		MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}


	float4 Position{ };
	Position.x = GameEngineRandom::MainRandom.RandomFloat(0, 100);
	Position.y = GameEngineRandom::MainRandom.RandomFloat(0, 100);


	float4 CurrentPos = GetTransform().GetWorldPosition();
	float4 DestPos = GetTransform().GetWorldPosition() + (Position * MoveDir_);
	float4 Move = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 5.f);

	GetTransform().SetWorldPosition(Move);

	if (GetTransform().GetWorldPosition().x <= 3643.f)
	{
		float4 Position{ 643.f, GetTransform().GetWorldPosition().y };

		GetTransform().SetWorldPosition(Position);
		MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}

	if (GetTransform().GetWorldPosition().x >= 6000.f)
	{
		float4 Position{ 6000.f, GetTransform().GetWorldPosition().y };

		GetTransform().SetWorldPosition(Position);
		MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}

	if (GetTransform().GetWorldPosition().y >= -600.f)
	{
		float4 Position{ GetTransform().GetWorldPosition().x,  -600.f };

		GetTransform().SetWorldPosition(Position);
		MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();

	}

	if (GetTransform().GetWorldPosition().y <= -900.f)
	{

		float4 Position{ GetTransform().GetWorldPosition().x, -900.f };

		GetTransform().SetWorldPosition(Position);
		MoveDir_.x = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		MoveDir_.y = GameEngineRandom::MainRandom.RandomFloat(-1, 1);
		ReSetAccTime();
	}
}

void GrimmStunBat::BatFlyEnd(const StateInfo& _Info)
{
}

void GrimmStunBat::BatMoveToGrimmStart(const StateInfo& _Info)
{
}

void GrimmStunBat::BatMoveToGrimmUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GrimmStunBat::BatMoveToGrimmEnd(const StateInfo& _Info)
{
}
