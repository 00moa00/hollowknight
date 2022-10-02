#include "PreCompile.h"
#include "KnightDoubleJumpParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

KnightDoubleJumpParticle::KnightDoubleJumpParticle() 
	:
	Scale_(1.0f)


{
}

KnightDoubleJumpParticle::~KnightDoubleJumpParticle() 
{
}

void KnightDoubleJumpParticle::Start()
{
	for (int i = 0; i < 20; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		float RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
		ParticleList_.back()->SetTexture("moth_feather_particle.png", RamdomIndex);

		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.6f, 1.0f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		81.f * RamdomScale,
		81.f * RamdomScale }
		);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-20.f, 20.0f);

		float4 RamPos;
		RamPos.x = GameEngineRandom::MainRandom.RandomFloat(-80.f, 80.0f);
		RamPos.y = GameEngineRandom::MainRandom.RandomFloat(-200.0f, 0.f);

		ParticleList_.back()->GetTransform().SetLocalPosition(RamPos);
		RotationSpeed_.push_back(GameEngineRandom::MainRandom.RandomFloat(-100.0f, 100.f));

		//ParticleList_.back()->GetTransform().SetLocalRotation({
		//0,
		//0,
		//RamdomRo }
		//);

		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());
		InitPos_.push_back(RamPos);
		ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");
		ScaleSpeed_.push_back(GameEngineRandom::MainRandom.RandomFloat(70.f, 200.0f));
	//	ScaleSpeed_.push_back(GameEngineRandom::MainRandom.RandomFloat(50.f, 100.0f));
	}

	Off();
}

void KnightDoubleJumpParticle::Update(float _DeltaTime)
{

	float4 Move = float4::DOWN * 100.f * _DeltaTime;

	for(int i =0 ; i < ParticleList_.size() ; ++i)
	{
		ParticleList_[i]->GetTransform().SetLocalMove(Move);
		ParticleList_[i]->GetTransform().SetLocalScale(ParticleList_[i]->GetTransform().GetLocalScale() - ScaleSpeed_[i] * _DeltaTime);
		ParticleList_[i]->GetTransform().SetLocalRotate({ 0, 0, RotationSpeed_ [i] * _DeltaTime});

		if (ParticleList_[i]->GetTransform().GetLocalScale().x <= 0.f)
		{
			ParticleList_[i]->Off();
		}
	}

	//for (int i = 0; i < ParticleList_.size(); ++i)
	//{
	//	if (ParticleList_[i]->GetTransform().GetLocalScale().x <= 0.f)
	//	{
	//		ParticleList_[i]->Off();
	//	}
	//}

}

void KnightDoubleJumpParticle::ParticleOn()
{
	On();

	Scale_ = 1.0f;

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		ParticleList_[i]->On();
		ParticleList_[i]->GetTransform().SetLocalScale(InitScale_[i]);
		ParticleList_[i]->GetTransform().SetLocalPosition(InitPos_[i]);

	}
}
