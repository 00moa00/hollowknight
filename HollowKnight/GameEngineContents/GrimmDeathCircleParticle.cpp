#include "PreCompile.h"
#include "GrimmDeathCircleParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmDeathCircleParticle::GrimmDeathCircleParticle() 
	:
	Scale_(1.0f),
	Length_(0.0f),
	Alpha_(1.0f),
	InitScale_(float4::ZERO)
{
}

GrimmDeathCircleParticle::~GrimmDeathCircleParticle() 
{
}

void GrimmDeathCircleParticle::Start()
{
	for (int i = 0; i < 50; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 4);
		ParticleList_.back()->SetTexture("grimm_smoke2.png", RamdomIndex);

		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(1.5f, 2.5f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		102.f * RamdomScale,
		128.f * RamdomScale }
		);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-20.f, 20.0f);

		ParticleList_.back()->GetTransform().SetLocalRotation({
		0,
		0,
		RamdomRo }
				);


		float RamdomAlpha = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);

		ParticleList_.back()->GetPixelData().MulColor.a = RamdomAlpha;

		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });
		float4 Len = GameEngineRandom::MainRandom.RandomFloat(50.f, 180.f);

		float4 Move = Len * Dir_.back().NormalizeReturn();

		ParticleList_.back()->GetTransform().SetLocalMove(Move);
	}

}

void GrimmDeathCircleParticle::Update(float _DeltaTime)
{
	//if (Scale_ <= 0.f)
	//{
	//	Scale_ = 0.f;
	//	this->Off();
	//}

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Move = Dir_[i].NormalizeReturn() * GameEngineRandom::MainRandom.RandomFloat(2000.f, 2500.f) * _DeltaTime;

		ParticleList_[i]->GetTransform().SetLocalMove(Move);
	}

	if (GetAccTime() > 1.0f)
	{
		this->Death();
	}
}

void GrimmDeathCircleParticle::ParticleOn()
{
	On();	
}

