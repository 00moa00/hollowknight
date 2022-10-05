#include "PreCompile.h"
#include "KnightScreamParticle.h"
#include <GameEngineBase/GameEngineRandom.h>

KnightScreamParticle::KnightScreamParticle() 
	:
	Scale_(1.0f),
	Alpha_(1.0f)
{
}

KnightScreamParticle::~KnightScreamParticle() 
{
}

void KnightScreamParticle::Start()
{
	for (int i = 0; i < 200; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());

		int Ram = GameEngineRandom::MainRandom.RandomInt(0, 1);

		if (Ram == 0)
		{
			ParticleList_.back()->SetTexture("black_fader.png");
			//ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

		}
		else
		{
			ParticleList_.back()->SetTexture("final_boss_glow_particle.png", 1);

			ParticleList_.back()->GetClonePipeLine()->SetOutputMergerBlend("AddBlend");

		}

		float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(0.7f,1.0f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		37.f * RamdomScale,
		37.f * RamdomScale }
		);

		//ParticleList_.back()->ScaleToCutTexture(0);
		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());

		Dir_.push_back({ GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f), GameEngineRandom::MainRandom.RandomFloat(-1.f, 1.f) });

		float4 Len;
		Len.x = GameEngineRandom::MainRandom.RandomFloat(0, 380.f);
		Len.y = GameEngineRandom::MainRandom.RandomFloat(0, 300.f);


		float4 Move = Len * Dir_.back().NormalizeReturn();
		Move.x = Len.x * Dir_.back().NormalizeReturn().x;
		Move.y = Len.y * Dir_.back().NormalizeReturn().y;


		RamSpeed_.push_back(GameEngineRandom::MainRandom.RandomFloat(150.f, 450.f));

		ParticleList_.back()->GetTransform().SetLocalMove(Move);
		InitPos_.push_back(ParticleList_.back()->GetTransform().GetLocalPosition());


		float RamAlpha = GameEngineRandom::MainRandom.RandomFloat(0.3f, 1.f);

		ParticleList_.back()->GetPixelData().MulColor.a = RamAlpha;

		InitAlpha_.push_back(RamAlpha);
	}
}

void KnightScreamParticle::Update(float _DeltaTime)
{
	if (GetAccTime() > 0.5f)
	{
		Scale_ -= 1.5f * _DeltaTime;
		if (Scale_ <= 0.f)
		{
			Scale_ = 0.f;
			Off();
		}

		Alpha_ -= 1.5f * _DeltaTime;
		if (Alpha_ <= 0.f)
		{
			Alpha_ = 0.f;
		}

		for (int i = 0; i < ParticleList_.size(); ++i)
		{
			float4 Move = float4::UP * RamSpeed_[i] * GameEngineTime::GetInst()->GetDeltaTime();

			ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetTransform().SetLocalScale({ InitScale_[i].x * Scale_, InitScale_[i].y * Scale_ });
			ParticleList_[i]->GetPixelData().MulColor.a = InitAlpha_[i] * Alpha_;
		}

		if (GetAccTime() > 1.5f)
		{
			Off();
		}
	}

	else
	{
		for (int i = 0; i < ParticleList_.size(); ++i)
		{
			float4 Move = Dir_[i].NormalizeReturn() * 120.f * GameEngineTime::GetInst()->GetDeltaTime();

			ParticleList_[i]->GetTransform().SetLocalMove(Move);
			ParticleList_[i]->GetTransform().SetLocalScale({ InitScale_[i].x * Scale_, InitScale_[i].y * Scale_ });
		}
	}
}

void KnightScreamParticle::ParticleOn()
{
	On();

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		ParticleList_[i]->GetTransform().SetLocalPosition(InitPos_[i]);
		ParticleList_[i]->GetTransform().SetLocalScale(InitScale_[i]);
		ParticleList_[i]->GetPixelData().MulColor.a = InitAlpha_[i];

	}

	Alpha_ = 1.0f;
	Scale_ = 1.0f;

	ReSetAccTime();

}
