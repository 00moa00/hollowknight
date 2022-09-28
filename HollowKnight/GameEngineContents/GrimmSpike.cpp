#include "PreCompile.h"

#include "GrimmSpike.h"
#include <GameEngineBase/GameEngineRandom.h>


GrimmSpike::GrimmSpike() 
	:
	Speed_(0.0f),
	CollMove_(0.0f),
	GrimmBirdStateManager()

{
}

GrimmSpike::~GrimmSpike() 
{
}

void GrimmSpike::Start()
{
	Speed_ = 1300.f;

	CreateCollisionComponent({ 30,1500 }, static_cast<int>(COLLISION_ORDER::Monster_Attack));
	GetCollision()->Off();

	CreateRendererComponent("Grimm Cln_Grimm_ground_spike0000-Sheet.png");
	GetRenderer()->CreateFrameAnimationCutTexture("START_UP", FrameAnimation_DESC("Grimm Cln_Grimm_ground_spike0000-Sheet.png", 0, 2, 0.040f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("GROW_UP", FrameAnimation_DESC("Grimm Cln_Grimm_ground_spike0000-Sheet.png", 3, 8, 0.020f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("GROW_DOWN", FrameAnimation_DESC("Grimm Cln_Grimm_ground_spike0000-Sheet.png", 8, 13, 0.020f, false));
	
	GetTransform().SetWorldRotation({0,0,GameEngineRandom::MainRandom.RandomFloat(-2.5f, 2.5f)});



	GetRenderer()->ChangeFrameAnimation("START_UP");
	//GetRenderer()->ScaleToCutTexture(0);
	GetRenderer()->GetTransform().SetWorldScale({148, 1600});

	GetRenderer()->AnimationBindEnd("GROW_DOWN", [=](const FrameAnimation_DESC& _Info)
		{		
			this->Death();

		});

	GrimmBirdStateManager.CreateStateMember("WAIT"
		, std::bind(&GrimmSpike::SpikeWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmSpike::SpikeWaitStart, this, std::placeholders::_1)
		, std::bind(&GrimmSpike::SpikeWaitEnd, this, std::placeholders::_1));

	GrimmBirdStateManager.CreateStateMember("MOVE_UP"
		, std::bind(&GrimmSpike::SpikeMoveUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmSpike::SpikeMoveUpStart, this, std::placeholders::_1)
		, std::bind(&GrimmSpike::SpikeMoveUpEnd, this, std::placeholders::_1));

	GrimmBirdStateManager.CreateStateMember("MOVE_UP_WAIT"
		, std::bind(&GrimmSpike::SpikeMoveUpWaitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmSpike::SpikeMoveUpWaitStart, this, std::placeholders::_1)
		, std::bind(&GrimmSpike::SpikeMoveUpWaitEnd, this, std::placeholders::_1));


	GrimmBirdStateManager.CreateStateMember("MOVE_DOWN"
		, std::bind(&GrimmSpike::SpikeMoveDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmSpike::SpikeMoveDownStart, this, std::placeholders::_1)
		, std::bind(&GrimmSpike::SpikeMoveDownEnd, this, std::placeholders::_1));



	GrimmBirdStateManager.ChangeState("WAIT");


}

void GrimmSpike::Update(float _DeltaTime)
{
	GrimmBirdStateManager.Update(_DeltaTime);
}

void GrimmSpike::SpikeWaitStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("START_UP");

}

void GrimmSpike::SpikeWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 1.0f)
	{
		GrimmBirdStateManager.ChangeState("MOVE_UP");

	}
}

void GrimmSpike::SpikeWaitEnd(const StateInfo& _Info)
{
}

void GrimmSpike::SpikeMoveUpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("GROW_UP");
	GetCollision()->On();
	GetCollision()->GetTransform().SetLocalPosition({0, -1500/2});
}

void GrimmSpike::SpikeMoveUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GetCollision()->GetTransform().GetLocalPosition().y < 0.f)
	{
		CollMove_ += 1000.f;

		GetCollision()->GetTransform().SetLocalPosition({ 0, _DeltaTime  * CollMove_ });

	}

	if (_Info.StateTime > 0.3f)
	{
		GrimmBirdStateManager.ChangeState("MOVE_UP_WAIT");
		return;
	}
}

void GrimmSpike::SpikeMoveUpEnd(const StateInfo& _Info)
{
}

void GrimmSpike::SpikeMoveUpWaitStart(const StateInfo& _Info)
{

}

void GrimmSpike::SpikeMoveUpWaitUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 0.2f)
	{
		GrimmBirdStateManager.ChangeState("MOVE_DOWN");
		return;
	}
}

void GrimmSpike::SpikeMoveUpWaitEnd(const StateInfo& _Info)
{
	GetCollision()->Off();

}

void GrimmSpike::SpikeMoveDownStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("GROW_DOWN");

}

void GrimmSpike::SpikeMoveDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void GrimmSpike::SpikeMoveDownEnd(const StateInfo& _Info)
{
}
