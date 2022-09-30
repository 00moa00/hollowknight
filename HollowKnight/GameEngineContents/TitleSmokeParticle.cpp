#include "PreCompile.h"
#include "TitleSmokeParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

TitleSmokeParticle::TitleSmokeParticle() 
	:
	AliveTimer_(0.f),
	Alpha_(0.8f),
	Speed_(0.f)
{
}

TitleSmokeParticle::~TitleSmokeParticle() 
{
}

void TitleSmokeParticle::Start()
{
	int RamIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ParticleRenderer_->SetTexture("wispy_smoke_particle_abyss.png", RamIndex);

	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(2.8f, 4.0f);
	ParticleRenderer_->GetTransform().SetLocalScale({ 102 * RamdomScale, 128 * RamdomScale });
	ParticleRenderer_->GetPixelData().MulColor.a = 0.8f;

	AliveTimer_ = GameEngineRandom::MainRandom.RandomFloat(5.f, 7.f);
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(20.f, 100.f);
}

void TitleSmokeParticle::Update(float _DeltaTime)
{
	float4 Move = float4::UP * Speed_ * _DeltaTime;

	GetTransform().SetLocalMove(Move);

	//AliveTimer_ += _DeltaTime;

	if (GetAccTime() >= AliveTimer_)
	{
		Alpha_ -= 0.8f * _DeltaTime;
		if (Alpha_ <= 0.0f)
		{
			Alpha_ = 0.f;
			this->Death();
		}
		ParticleRenderer_->GetPixelData().MulColor.a = Alpha_;

		//ParticleRenderer_->GetTransform().SetLocalScale({ ParticleRenderer_->GetTransform().GetLocalScale().x * Scale_,
		//	ParticleRenderer_->GetTransform().GetLocalScale().y * Scale_ });
	}
}

