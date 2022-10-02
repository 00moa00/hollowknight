#include "PreCompile.h"
#include "MapWhitParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "HollowKnightLevel.h"

MapWhitParticle::MapWhitParticle() 
	:
	AliveTimer_(0.0f),
	Alpha_(1.0f),
	Scale_(1.0f),
	Speed_(0.f),
	MapMaxX_(0.f),


	isWind_(false),

	Dir_(float4::ZERO)
{
}

MapWhitParticle::~MapWhitParticle() 
{
}

void MapWhitParticle::Start()
{
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	int RamTex = GameEngineRandom::MainRandom.RandomFloat(0, 1);

	if (RamTex == 0)
	{
		ParticleRenderer_->SetTexture("Default-Particle.png");

	}
	else
	{
		ParticleRenderer_->SetTexture("final_boss_glow_particle.png", 1);

	}


	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.4f, 2.5f);
	ParticleRenderer_->GetTransform().SetLocalScale({ 37.f * RamdomScale, 37.f * RamdomScale });
	Alpha_ = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f);

	ParticleRenderer_->GetPixelData().MulColor.a = Alpha_;

	AliveTimer_ = GameEngineRandom::MainRandom.RandomFloat(20.f, 30.f);
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(5.f, 20.f);
	Dir_.x = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.f);
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.f);
	Dir_.Normalize();

	float X = GameEngineRandom::MainRandom.RandomFloat(0, GetLevel<HollowKnightLevel>()->GetMapSize().x);
	float Y = GameEngineRandom::MainRandom.RandomFloat(-GetLevel<HollowKnightLevel>()->GetMapSize().y, 0);

	float4 Pos = { X ,Y, static_cast<float>(Z_ORDER::Back_Object) };
	GetTransform().SetWorldPosition(Pos);


}

void MapWhitParticle::Update(float _DeltaTime)
{
	if (isWind_ == false)
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

	else
	{
		float4 Move = Dir_ * Speed_ * _DeltaTime;

		GetTransform().SetLocalMove(Move);

		if (GetTransform().GetLocalPosition().x > MapMaxX_ + 300.f)
		{
			this->Death();
		}
	}
	
}

void MapWhitParticle::SetWindMove()
{
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(500.f, 650.f);
	Dir_.x = 1.0f;
	Dir_.y = GameEngineRandom::MainRandom.RandomFloat(-0.2f, 0.3f);
	Dir_.Normalize();

	MapMaxX_ = GetLevel<HollowKnightLevel>()->GetMapSize().x;


}

