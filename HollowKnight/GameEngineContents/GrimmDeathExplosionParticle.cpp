#include "PreCompile.h"
#include "GrimmDeathExplosionParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmDeathExplosionParticle::GrimmDeathExplosionParticle() 
	:
	Scale_(1.0f),
	Length_(0.0f),
	Alpha_(1.0f),
	InitScale_(float4::ZERO)
{
}

GrimmDeathExplosionParticle::~GrimmDeathExplosionParticle() 
{
}

void GrimmDeathExplosionParticle::Start()
{
	for (int i = 0; i < 50; ++i)
	{
		//ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		ParticleList_.back()->SetTexture("grimm_smoke2.png", RamdomIndex);


		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(4.5f, 5.0f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		102.f * RamdomScale,
		128.f * RamdomScale }
		);

		ParticleList_.back()->ScaleToCutTexture(0);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-20.f, 20.0f);

		ParticleList_.back()->GetTransform().SetLocalRotation({
		0,
		0,
		RamdomRo }
		);

		float RamdomAlpha = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);

		ParticleList_.back()->GetPixelData().MulColor.a = RamdomAlpha;

		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });
		float4 Len = GameEngineRandom::MainRandom.RandomFloat(0.f, 200.f);
		
		float4 Move = Len * Dir_.back().NormalizeReturn();

		ParticleList_.back()->GetTransform().SetLocalMove(Move);
	}
}

void GrimmDeathExplosionParticle::Update(float _DeltaTime)
{
	if (GetAccTime() > 1.5f)
	{
		Alpha_ -= 1.5f * _DeltaTime;

		if (Alpha_ <= 0)
		{
			Alpha_ = 0.f;
		}

		for (int i = 0; i < ParticleList_.size(); ++i)
		{
		//	float4 Move = Dir_[i].NormalizeReturn() * 2500.f * _DeltaTime;

		//	ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetPixelData().MulColor.a = Alpha_;
		}
		//this->Death();
	}

	else
	{
		Alpha_ -= 0.5f * _DeltaTime;

		if (Alpha_ <= 0)
		{
			Alpha_ = 0.f;
		}

		for (int i = 0; i < ParticleList_.size(); ++i)
		{
			float4 Move = Dir_[i].NormalizeReturn() * GameEngineRandom::MainRandom.RandomFloat(20.f, 70.f) * _DeltaTime;

			ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetPixelData().MulColor.a = Alpha_;
		}
	}
}

void GrimmDeathExplosionParticle::ParticleOn()
{
	On();
}

void GrimmDeathExplosionParticle::MoveFast()
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Move = Dir_[i].NormalizeReturn() * 2500.f * GameEngineTime::GetInst()->GetDeltaTime();

		ParticleList_[i]->GetTransform().SetLocalMove(Move);
		//GrimmDeathExplosionParticleList_[i]->GetPixelData().MulColor.a = Alpha_;
	}
}

