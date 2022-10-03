#include "PreCompile.h"
#include "HeartPieceWhiteParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

HeartPieceWhiteParticle::HeartPieceWhiteParticle() 
	:
	Scale_(1.0f)
{
}

HeartPieceWhiteParticle::~HeartPieceWhiteParticle() 
{
}

void HeartPieceWhiteParticle::Start()
{
	for (int i = 0; i < 50; ++i)
	{
		//ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		ParticleList_.push_back(CreateComponent<GameEngineUIRenderer>());
		ParticleList_.back()->SetTexture("final_boss_glow_particle.png", 1);


		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(4.5f, 5.0f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		37.f * RamdomScale,
		37.f * RamdomScale }
		);

		ParticleList_.back()->ScaleToCutTexture(0);
		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());

		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });

		float4 Len = GameEngineRandom::MainRandom.RandomFloat(0.f, 200.f);
		Len.x = GameEngineRandom::MainRandom.RandomFloat(-100.f, 100.f);
		Len.y = GameEngineRandom::MainRandom.RandomFloat(-30.f, 30.f);


		float4 Move = Len * Dir_.back().NormalizeReturn();
		Move.x = Len.x * Dir_.back().NormalizeReturn().x;
		Move.y = Len.x * Dir_.back().NormalizeReturn().y;



		ParticleList_.back()->GetTransform().SetLocalMove(Move);
	}
}

void HeartPieceWhiteParticle::Update(float _DeltaTime)
{

	if (GetAccTime() > 2.f)
	{
		Scale_ -= 0.7f * _DeltaTime;
		if (Scale_ <= 0.f)
		{
			Scale_ = 0.f;
			this->Death();
		}

		for (int i = 0; i < ParticleList_.size(); ++i)
		{
			float4 Move = Dir_[i].NormalizeReturn() * 1500.f * GameEngineTime::GetInst()->GetDeltaTime();

			ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetTransform().SetLocalScale({ InitScale_[i].x * Scale_, InitScale_[i].y * Scale_ });
		}
	}

	else
	{
		for (int i = 0; i < ParticleList_.size(); ++i)
		{
			float4 Move = Dir_[i].NormalizeReturn() * 100.f * GameEngineTime::GetInst()->GetDeltaTime();

			ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetTransform().SetLocalScale({ InitScale_[i].x * Scale_, InitScale_[i].y * Scale_ });

		}
	}
}

