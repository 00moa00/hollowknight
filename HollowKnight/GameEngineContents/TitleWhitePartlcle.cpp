#include "PreCompile.h"
#include "TitleWhitePartlcle.h"
#include <GameEngineBase/GameEngineRandom.h>

TitleWhitePartlcle::TitleWhitePartlcle() 
	:
	AliveTimer_(0.0f), 
	Alpha_(1.0f),
	Scale_(1.0f),
	Speed_(0.f),

	Dir_(float4::ZERO)
{
}

TitleWhitePartlcle::~TitleWhitePartlcle() 
{
}

void TitleWhitePartlcle::Start()
{

//	int RamIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ParticleRenderer_->SetTexture("final_boss_glow_particle.png", 1);

	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.4f, 0.6f);
	ParticleRenderer_->GetTransform().SetLocalScale({ 37.f * RamdomScale, 37.f * RamdomScale });
	Alpha_ = GameEngineRandom::MainRandom.RandomFloat(0.8f, 1.0f);
	
	ParticleRenderer_->GetPixelData().MulColor.a = Alpha_;

	AliveTimer_ = GameEngineRandom::MainRandom.RandomFloat(7.f, 10.f);
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(5.f, 20.f);
	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.f);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.f);
	Dir_.Normalize();
}

void TitleWhitePartlcle::Update(float _DeltaTime)
{
	float4 Move = Dir_ * Speed_ * _DeltaTime;

	GetTransform().SetLocalMove(Move);

	//AliveTimer_ += _DeltaTime;

	if (GetAccTime() >= AliveTimer_)
	{
		Alpha_ -= 0.8f * _DeltaTime;
		Scale_ -= 0.8f * _DeltaTime;

		if (Alpha_ <= 0.0f)
		{
			Alpha_ = 0.f;
			//this->Death();
		}

		if (Scale_ <= 0.0f)
		{
			Scale_ = 0.f;
			this->Death();
		}

		ParticleRenderer_->GetPixelData().MulColor.a = Alpha_;
		//ParticleRenderer_->Set
		ParticleRenderer_->GetTransform().SetLocalScale({ ParticleRenderer_->GetTransform().GetLocalScale().x * Scale_,
			ParticleRenderer_->GetTransform().GetLocalScale().y * Scale_ });
	}
}

