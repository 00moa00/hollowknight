#include "Precompile.h"
#include "MonsterHitPuffEffect.h"
#include "HollowKnightLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

MonsterHitPuffEffect::MonsterHitPuffEffect() 
{
}

MonsterHitPuffEffect::~MonsterHitPuffEffect() 
{
}

void MonsterHitPuffEffect::Start()
{
	Speed_ = 1500.f;

	for (int i = 0; i < 7; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		ParticleList_.back()->SetTexture("orange_puff_animated.png");

		ParticleList_.back()->CreateFrameAnimationCutTexture("SHOT_ANIMATION", FrameAnimation_DESC("orange_puff_animated.png", 0, 9, 0.080f, false));
		ParticleList_.back()->ChangeFrameAnimation("SHOT_ANIMATION");

	//	ParticleList_.back()->ScaleToCutTexture(0);
		float RamdomScale= GameEngineRandom::MainRandom.RandomFloat(0.6f, 0.9f);

		ParticleList_.back()->GetTransform().SetLocalScale({
		82.f* RamdomScale
		,77.f * RamdomScale }
		);

		float RamdomAlpha = GameEngineRandom::MainRandom.RandomFloat(0.3f, 1.0f);

		ParticleList_.back()->GetPixelData().MulColor.a = RamdomAlpha;


		//InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());

		//isEndMove_.push_back(false);
	}
}

void MonsterHitPuffEffect::Update(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		if (StartDirList_[i].CompareInt2D(float4::RIGHT))
		{
			DirList_[i].x += 0.00001f;
			DirList_[i].y -= 0.00001f;

			ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
		}

		if (StartDirList_[i].CompareInt2D(float4::LEFT))
		{
			DirList_[i].x -= 0.00001f;

			DirList_[i].y -= 0.00001f;
			ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
		}

		if (StartDirList_[i].CompareInt2D(float4::UP))
		{
			if (InitDir_[i].x >= 0.f)
			{
				DirList_[i].x += 0.00001f;
			}

			else
			{
				DirList_[i].x -= 0.00001f;
			}
			DirList_[i].y -= 0.00001f;
			ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
		}

		if (StartDirList_[i].CompareInt2D(float4::DOWN))
		{

			if (InitDir_[i].x >= 0.f)
			{
				DirList_[i].x += 0.00001f;
			}

			else
			{
				DirList_[i].x -= 0.00001f;
			}

			DirList_[i].y += -0.00001f;
			ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
		}

		if (ParticleList_[i]->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() == 9)
		{
			ParticleList_[i]->Off();
		}

	}

	if (GetAccTime() > 5.0f)
	{
		this->Death();
	}
}

void MonsterHitPuffEffect::SetDir(float4 _Dir)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Dir;
		_Dir.Normalize();
		if (_Dir.CompareInt2D(float4::RIGHT))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 0.3f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.1f, 0.1f);

			StartDirList_.push_back(float4::RIGHT);
			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::LEFT))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.3f, 0.f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.1f, 0.1f);

			StartDirList_.push_back(float4::LEFT);
			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::UP))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.15f, 0.15f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(0.f, 0.1f);

			StartDirList_.push_back(float4::UP);

			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::DOWN))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.15f, 0.15f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.1f, 0.f);
			StartDirList_.push_back(float4::DOWN);

			DirList_.push_back(Dir);
		}

		else
		{

			StartDirList_.push_back(float4::ZERO);

			DirList_.push_back(float4::ZERO);

		}

		InitDir_.push_back(Dir);
	}
}

