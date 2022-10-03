#include "PreCompile.h"
#include "GrimmFlameParticle.h"
#include <GameEngineBase/GameEngineRandom.h>


GrimmFlameParticle::GrimmFlameParticle() 
{
}

GrimmFlameParticle::~GrimmFlameParticle() 
{
}

void GrimmFlameParticle::Start()
{
	for (int i = 0; i < 30; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 8);
		ParticleList_.back()->SetTexture("grimm_particle_flame2.png", RamdomIndex);
		ParticleList_.back()->ScaleToCutTexture(RamdomIndex);

		ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.7f);


		if (i > 5)
		{
			//ParticleList_.back()->SetTexture("grimm_particle_flame2.png");
			ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");
			int Scale = GameEngineRandom::MainRandom.RandomFloat(3.8f, 4.0f);
			ParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.2f);
			ParticleList_.back()->GetTransform().SetWorldScale(ParticleList_.back()->GetTransform().GetWorldScale() * Scale);
		}

		else
		{
			ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");
			int Scale = GameEngineRandom::MainRandom.RandomFloat(2.2f, 2.5f);

			ParticleList_.back()->GetTransform().SetWorldScale(ParticleList_.back()->GetTransform().GetWorldScale() * Scale);
		}
	}
}

void GrimmFlameParticle::Update(float _DeltaTime)
{
	static float timer = 0; // 0 - 4(sec)
	timer += _DeltaTime;
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		r = GameEngineRandom::MainRandom.RandomFloat(20, 30.f); // angle(degree)
		a = GameEngineRandom::MainRandom.RandomFloat(10, 20.0f); // angle(degree)
		ParticleList_[i]->GetTransform().SetLocalPosition({ cosf(a * 0.01745f) * r,sinf(a * 0.01745f) * r });
		//ParticleList_[i]->GetPixelData().MulColor.a = fabsf(sinf(3.141592f * timer * 0.5f * 0.5f));
	}
}

