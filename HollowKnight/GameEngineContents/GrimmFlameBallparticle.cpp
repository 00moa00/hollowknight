#include "PreCompile.h"
#include "GrimmFlameBallparticle.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmFlameBallparticle::GrimmFlameBallparticle()
	:
	Scale_(1.0f),
	Length_(0.0f),
	Alpha_(1.0f),
	InitScale_(float4::ZERO)
{
}

GrimmFlameBallparticle::~GrimmFlameBallparticle() 
{
}

void GrimmFlameBallparticle::Start()
{
	for (int i = 0; i < 35; ++i)
	{
		BallParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
		BallParticleList_.back()->SetTexture("Grimm_flame_ball_particle.png", RamdomIndex);
		BallParticleList_.back()->ScaleToCutTexture(RamdomIndex);
		int Scale = GameEngineRandom::MainRandom.RandomFloat(3.4f, 3.8f);
		BallParticleList_.back()->GetTransform().SetWorldScale(BallParticleList_.back()->GetTransform().GetWorldScale() * Scale);
		BallParticleList_.back()->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.7f);
		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f)});
		float4 Len = Length_;
		float4 Move = Len * Dir_.back().NormalizeReturn();

		BallParticleList_.back()->GetTransform().SetLocalMove(Move);
		InitPos_.push_back(BallParticleList_.back()->GetTransform().GetLocalPosition());

		ScaleList_.push_back(BallParticleList_.back()->GetTransform().GetWorldScale() * Scale);
		//InitScale_ = BallParticleList_.back()->GetTransform().GetWorldScale() * 3.5f;

	}
}

void GrimmFlameBallparticle::Update(float _DeltaTime)
{
	Scale_ -= 2.0f * _DeltaTime;
	////Alpha_ -= 2.7f * _DeltaTime;

	if (Scale_ <= 0.f)
	{
		Scale_ = 0.f;
		this->Off();
	}

	//if (Alpha_ <= 0.0f)
	//{
	//	Alpha_ = 0.f;
	//}

	for (int i = 0; i < 30; ++i)
	{
		
		float4 Move = Dir_[i].NormalizeReturn() * GameEngineRandom::MainRandom.RandomFloat(450.f, 650.f) * _DeltaTime;

		BallParticleList_[i]->GetTransform().SetLocalMove(Move);
		BallParticleList_[i]->GetTransform().SetWorldScale(ScaleList_[i] * Scale_);


		//BallParticleList_[i]->GetPixelData().MulColor.a = Alpha_;
	}
}

void GrimmFlameBallparticle::FlameBallparticleOn()
{
	On();
	for (int i = 0; i < 35; ++i)
	{

		BallParticleList_.back()->GetTransform().SetWorldScale(ScaleList_[i]);
		BallParticleList_.back()->GetTransform().SetLocalPosition(InitPos_[i]);

	}
}

