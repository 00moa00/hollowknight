#include "PreCompile.h"
#include "MonsterDeathPuffParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

MonsterDeathPuffParticle::MonsterDeathPuffParticle() 
	:
	Scale_(1.0f),
	Length_(0.0f),
	Alpha_(1.0f),
	InitScale_(float4::ZERO)
{
}

MonsterDeathPuffParticle::~MonsterDeathPuffParticle() 
{
}

void MonsterDeathPuffParticle::Start()
{
	for (int i = 0; i < 40; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		ParticleList_.back()->SetTexture("orange_puff_animated.png");

		ParticleList_.back()->CreateFrameAnimationCutTexture("SHOT_ANIMATION", FrameAnimation_DESC("orange_puff_animated.png", 0, 9, 0.070f, false));
		ParticleList_.back()->ChangeFrameAnimation("SHOT_ANIMATION");

		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.6f, 0.9f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		82.f * RamdomScale
		,77.f * RamdomScale }
		);

		float RamdomAlpha = GameEngineRandom::MainRandom.RandomFloat(0.1f, 1.0f);

		ParticleList_.back()->GetPixelData().MulColor.a = RamdomAlpha;
				
		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });
		float4 Len = GameEngineRandom::MainRandom.RandomFloat(0.f, 140.f);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f);
		ParticleList_.back()->GetTransform().SetWorldRotation({0,0,RamdomRo });


		float4 Move = Len * Dir_.back().NormalizeReturn();

		ParticleList_.back()->GetTransform().SetLocalMove(Move);
		//InitPos_.push_back(ParticleList_.back()->GetTransform().GetLocalPosition());
		//ScaleList_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());
	}
}

void MonsterDeathPuffParticle::Update(float _DeltaTime)
{
	Scale_ -= 2.0f * _DeltaTime;

	if (Scale_ <= 0.f)
	{
		Scale_ = 0.f;
		this->Off();
	}

	for (int i = 0; i < ParticleList_.size(); ++i)
	{

		float4 Move = Dir_[i].NormalizeReturn() * GameEngineRandom::MainRandom.RandomFloat(5.f, 100.f) * _DeltaTime;

		ParticleList_[i]->GetTransform().SetLocalMove(Move);
		if (ParticleList_[i]->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() == 9)
		{
			ParticleList_[i]->Off();
		}
		//ParticleList_[i]->GetTransform().SetWorldScale(ScaleList_[i] * Scale_);
	}

	if (GetAccTime() > 5.0f)
	{
		this->Death();
	}
}

void MonsterDeathPuffParticle::ParticleOn()
{
	On();
	Scale_ = 1.0f;

	//for (int i = 0; i < ParticleList_.size(); ++i)
	//{

	//	ParticleList_[i]->GetTransform().SetWorldScale(ScaleList_[i]);
	//	ParticleList_[i]->GetTransform().SetLocalPosition(InitPos_[i]);

	//}
}

