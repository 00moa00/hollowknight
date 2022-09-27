#include "PreCompile.h"
#include "GrimmCastPillarEffect.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmCastPillarEffect::GrimmCastPillarEffect() 
	:
	a(0.0f),
	r(0.0f)
{
}

GrimmCastPillarEffect::~GrimmCastPillarEffect() 
{
}

void GrimmCastPillarEffect::Start()
{
	for (int i = 0; i < 35; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 8);
		ParticleList_.back()->SetTexture("grimm_particle_flame.png", RamdomIndex);
		ParticleList_.back()->ScaleToCutTexture(RamdomIndex);
		ParticleList_.back()->GetTransform().SetWorldScale({
		 100.f + GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f)
		,700.f + GameEngineRandom::MainRandom.RandomFloat(-100.f, 100.f) }
		);

		ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.3f, 0.7f);

		float4 Move;
		Move.x = 0.f;
		Move.x = { GameEngineRandom::MainRandom.RandomFloat(100.f, 200.f) };
		Move.y= { GameEngineRandom::MainRandom.RandomFloat(100.f, 200.f) };

		int Ram = GameEngineRandom::MainRandom.RandomInt(0, 2);

		if (Ram == 0)
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f) };
			Move.y = { GameEngineRandom::MainRandom.RandomFloat(100.f, 400.f) };
		}

		else if (Ram == 2)
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f) };
			Move.y = { GameEngineRandom::MainRandom.RandomFloat(-300.f, -100.f) };
		}
		else
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-40.f, 40.f) };
			Move.y = 0.f;
			ParticleList_.back()->GetPipeLine()->SetOutputMergerBlend("AddBlend");

		}

		ParticleList_.back()->GetTransform().SetLocalMove(Move);
		InitPos_.push_back(ParticleList_.back()->GetTransform().GetLocalPosition());
	}



	CastPillarManager_.CreateStateMember("FIRE"
		, std::bind(&GrimmCastPillarEffect::CastPillarFireUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmCastPillarEffect::CastPillarFireStart, this, std::placeholders::_1)
		, std::bind(&GrimmCastPillarEffect::CastPillarFireEnd, this, std::placeholders::_1));


	CastPillarManager_.CreateStateMember("DISAPPEAR"
		, std::bind(&GrimmCastPillarEffect::CastPillarDisappearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&GrimmCastPillarEffect::CastPillarDisappearStart, this, std::placeholders::_1)
		, std::bind(&GrimmCastPillarEffect::CastPillarDisappearEnd, this, std::placeholders::_1));

	CastPillarManager_.ChangeState("FIRE");

}

void GrimmCastPillarEffect::Update(float _DeltaTime)
{
	CastPillarManager_.Update(_DeltaTime);

}


void GrimmCastPillarEffect::CastPillarEffectOn()
{
	On();
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		ParticleList_[i]->GetTransform().SetWorldPosition(InitPos_[i]);
		ParticleList_[i]->On();
	}
}

void GrimmCastPillarEffect::CaetPillarEffectOff()
{
	Off();
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		ParticleList_[i]->Off();
	}
}

void GrimmCastPillarEffect::CastPillarFireStart(const StateInfo& _Info)
{
}

void GrimmCastPillarEffect::CastPillarFireUpdate(float _DeltaTime, const StateInfo& _Info)
{

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		a = GameEngineRandom::MainRandom.RandomFloat(10, 30.0f); // angle(degree)
		r = GameEngineRandom::MainRandom.RandomFloat(10, 20.f); // angle(degree)
		ParticleList_[i]->GetTransform().SetLocalPosition({ cosf(a * 0.01745f) * r,sinf(a * 0.01745f) * r });
		float4 MoveUp;
		MoveUp.y = GameEngineRandom::MainRandom.RandomFloat(200.f, 500.f);

	}

	if (_Info.StateTime > 0.5f)
	{
		CastPillarManager_.ChangeState("DISAPPEAR");
	}


}

void GrimmCastPillarEffect::CastPillarFireEnd(const StateInfo& _Info)
{
}

void GrimmCastPillarEffect::CastPillarDisappearStart(const StateInfo& _Info)
{
}

void GrimmCastPillarEffect::CastPillarDisappearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		a = GameEngineRandom::MainRandom.RandomFloat(10, 30.0f); // angle(degree)
		r = GameEngineRandom::MainRandom.RandomFloat(10, 20.f); // angle(degree)
		ParticleList_[i]->GetTransform().SetLocalPosition({ cosf(a * 0.01745f) * r,ParticleList_[i]->GetTransform().GetLocalPosition().y + sinf(a * 0.01745f) * r });
		float4 MoveUp;
		MoveUp.y = GameEngineRandom::MainRandom.RandomFloat(500.f, 800.f);
		ParticleList_[i]->GetTransform().SetLocalMove(MoveUp * _DeltaTime);

		int Ram = GameEngineRandom::MainRandom.RandomInt(0, 10);
		if (Ram == 0)
		{
			ParticleList_[i]->Off();
		}
	}
}

void GrimmCastPillarEffect::CastPillarDisappearEnd(const StateInfo& _Info)
{
}
