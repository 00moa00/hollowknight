#include "PreCompile.h"
#include "GrimmDeathSmallParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmDeathSmallParticle::GrimmDeathSmallParticle() 
	:
	Scale_(1.0f),
	Length_(0.0f),
	Alpha_(1.0f)
{
}

GrimmDeathSmallParticle::~GrimmDeathSmallParticle() 
{
}

void GrimmDeathSmallParticle::Start()
{
	for (int i = 0; i < 55; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		float RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
		ParticleList_.back()->SetTexture("white_hit_particle_Pink.png", RamdomIndex);

		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.2f, 0.4f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		64.f * RamdomScale,
		64.f * RamdomScale }
		);

		//float RamdomAlpha = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);

		//ParticleList_.back()->GetPixelData().MulColor.a = RamdomAlpha;
		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });
		float4 Len = GameEngineRandom::MainRandom.RandomFloat(50.f, 180.f);


		float4 Move = Len * Dir_.back().NormalizeReturn();
		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());
		ParticleList_.back()->GetTransform().SetLocalMove(Move);

	}
}

void GrimmDeathSmallParticle::Update(float _DeltaTime)
{
	Scale_ += 0.2f * _DeltaTime;

	if (Scale_ <= 2.5f)
	{
		Scale_ = 2.5f;
		//this->Off();
	}

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Move = Dir_[i].NormalizeReturn() * GameEngineRandom::MainRandom.RandomFloat(2000.f, 2500.f) * _DeltaTime;

		ParticleList_[i]->GetTransform().SetLocalMove(Move);
		ParticleList_[i]->GetTransform().SetLocalScale(InitScale_[i] * Scale_);
	}

	if (GetAccTime() > 1.0f)
	{
		this->Death();
	}


}

void GrimmDeathSmallParticle::ParticleOn()
{
	On();
}

