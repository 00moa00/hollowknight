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

	GetTransform().SetWorldPosition({ 0, -50 });
	for (int i = 0; i < 75; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		ParticleList_.back()->SetTexture("grimm_smoke.png", RamdomIndex);
		ParticleList_.back()->ScaleToCutTexture(RamdomIndex);
		ParticleList_.back()->GetTransform().SetWorldScale({
		 150.f + GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f)
		,800.f + GameEngineRandom::MainRandom.RandomFloat(-100.f, 100.f) }
		);


		float4 Move;
		Move.x = 0.f;

		Move.x = { GameEngineRandom::MainRandom.RandomFloat(100.f, 200.f) };
		Move.y= { GameEngineRandom::MainRandom.RandomFloat(100.f, 200.f) };

		int Ram = GameEngineRandom::MainRandom.RandomInt(0, 2);

		if (i == 0)
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f) };
			Move.y = { GameEngineRandom::MainRandom.RandomFloat(100.f, 400.f) };
			//ParticleList_.back()->GetPixelData().PlusColor.r = 1.0f;
			//ParticleList_.back()->GetPixelData().MulColor.r = 1.0f;
			ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.3f, 0.5f);
		//	ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("Overlay");
			ParticleList_.back()->SetTexture("grimm_smoke2.png");

		}

		else if (i == 2)
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f) };
			Move.y = { GameEngineRandom::MainRandom.RandomFloat(-300.f, -100.f) };
			//ParticleList_.back()->GetPixelData().PlusColor.r = 1.0f;
			//ParticleList_.back()->GetPixelData().MulColor.r = 1.0f;
			//ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("Overlay");
			ParticleList_.back()->SetTexture("grimm_smoke2.png");

			ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.3f, 0.5f);

		}
		else
		{
			Move.x = { GameEngineRandom::MainRandom.RandomFloat(-20.f, 20.f) };
			Move.y = 0.f;
			ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

			//ParticleList_.back()->SetTexture("grimm_smoke.png");
			ParticleList_.back()->GetTransform().SetWorldScale({
			 100.f + GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f)
			,550.f + GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f) }
			);

			if (i > 10)
			{
				ParticleList_.back()->GetTransform().SetWorldScale({
				 50.f 
				,300.f }
				);

			}
			//ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.2f, 0.7f);

		}

		//ParticleList_.back()->GetTransform().SetLocalMove(Move);
		//ParticleList_.back()->InstancingOn();
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
		ParticleList_[i]->GetTransform().SetLocalPosition(InitPos_[i]);
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
		r = GameEngineRandom::MainRandom.RandomFloat(30, 40.f); // angle(degree)
		a = GameEngineRandom::MainRandom.RandomFloat(30, 40.0f); // angle(degree)
		ParticleList_[i]->GetTransform().SetLocalPosition({ cosf(a * 0.01745f) * r,sinf(a * 0.01745f) * r });
		float4 MoveUp;
		MoveUp.y = GameEngineRandom::MainRandom.RandomFloat(200.f, 500.f);

	}

	if (_Info.StateTime > 0.1f)
	{
		CastPillarManager_.ChangeState("DISAPPEAR");
		return;
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
		MoveUp.y = GameEngineRandom::MainRandom.RandomFloat(1200.f, 1300.f);
		ParticleList_[i]->GetTransform().SetLocalMove(MoveUp * _DeltaTime);

		int Ram = GameEngineRandom::MainRandom.RandomInt(0, 5);
		if (Ram == 0)
		{
			ParticleList_[i]->Off();
		}
	}
}

void GrimmCastPillarEffect::CastPillarDisappearEnd(const StateInfo& _Info)
{
}
