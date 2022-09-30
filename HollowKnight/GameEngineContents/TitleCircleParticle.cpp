#include "PreCompile.h"
#include "TitleCircleParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

TitleCircleParticle::TitleCircleParticle()
	:
	ParticleRenderer_(nullptr),

	AliveTimer_(0.0f),
	Scale_(1.0f)
{
}

TitleCircleParticle::~TitleCircleParticle() 
{
}

void TitleCircleParticle::Start()
{
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ParticleRenderer_->SetTexture("particle_01.png");

	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.7f, 1.3f);
	ParticleRenderer_->GetTransform().SetLocalScale({28 * RamdomScale, 28 * RamdomScale });


	AliveTimer_ = GameEngineRandom::MainRandom.RandomFloat(5.f,12.f);
	Speed_ = GameEngineRandom::MainRandom.RandomFloat(20.f, 100.f);
}

void TitleCircleParticle::Update(float _DeltaTime)
{

	float4 Move = float4::UP * Speed_ * _DeltaTime;

	GetTransform().SetLocalMove(Move);

	//AliveTimer_ += _DeltaTime;

	if (GetAccTime() >= AliveTimer_)
	{
		Scale_ -= 0.7f * _DeltaTime;



	ParticleRenderer_->GetTransform().SetLocalScale({ ParticleRenderer_->GetTransform().GetLocalScale().x * Scale_,
		ParticleRenderer_->GetTransform().GetLocalScale().y * Scale_ });

	if (Scale_ <= 0.0f)
	{
		Scale_ = 0.f;
		this->Death();
	}
		
	}

}

