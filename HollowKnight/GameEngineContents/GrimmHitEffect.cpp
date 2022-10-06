#include "PreCompile.h"
#include "GrimmHitEffect.h"
#include "HollowKnightLevel.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmHitEffect::GrimmHitEffect() 
	:
	isImpact_(true),

	Scale_(1.0f),
	Speed_(0.0f)
{
}

GrimmHitEffect::~GrimmHitEffect() 
{
}

void GrimmHitEffect::Start()
{
	Speed_ = 1500.f;

	for (int i = 0; i < 40; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
		ParticleList_.back()->SetTexture("white_hit_particle.png", RamdomIndex);
		ParticleList_.back()->ScaleToCutTexture(RamdomIndex);


		ParticleList_.back()->GetTransform().SetLocalScale({
		ParticleList_.back()->GetTransform().GetLocalScale().x * 0.65f
		,	ParticleList_.back()->GetTransform().GetLocalScale().y * 0.65f }
		);



		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());


		isEndMove_.push_back(false);
	}
}

void GrimmHitEffect::Update(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		if (StartDirList_[i].CompareInt2D(float4::RIGHT))
		{
			DirList_[i].x += 0.001f;
			DirList_[i].y -= 0.01f;

			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (StartDirList_[i].CompareInt2D(float4::LEFT))
		{
			DirList_[i].x -= 0.001f;

			DirList_[i].y -= 0.01f;
			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (StartDirList_[i].CompareInt2D(float4::UP))
		{
			if (InitDir_[i].x >= 0.f)
			{
				DirList_[i].x += 0.01f;
			}

			else
			{
				DirList_[i].x -= 0.01f;
			}
			DirList_[i].y -= 0.01f;
			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (StartDirList_[i].CompareInt2D(float4::DOWN))
		{

			if (InitDir_[i].x >= 0.f)
			{
				DirList_[i].x += 0.01f;
			}

			else
			{
				DirList_[i].x -= 0.01f;
			}

			DirList_[i].y += -0.01f;
			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (GetAccTime() > 3.0f)
		{
			Death();
		}
	/*	Scale_ -= 0.08f * _DeltaTime;
		if (Scale_ <= 0.f)
		{
			ParticleList_[i]->Off();
			Scale_ = 0.f;
			this->Death();
		}*/

		ParticleList_[i]->GetTransform().SetLocalScale(InitScale_[i] * Scale_);


	}

}

void GrimmHitEffect::SetDir(float4 _Dir)
{

	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Dir;
		_Dir.Normalize();
		if (_Dir.CompareInt2D(float4::RIGHT))
		{
			int RamDir = GameEngineRandom::MainRandom.RandomInt(0, 4);
			if (RamDir == 0)
			{
				Dir.x = GameEngineRandom::MainRandom.RandomFloat(-1.f, 0.f);
				Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);

				StartDirList_.push_back(float4::LEFT);
				DirList_.push_back(Dir);
			}
			else
			{
				Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
				Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);

				StartDirList_.push_back(float4::RIGHT);
				DirList_.push_back(Dir);
			}


		}
		else if (_Dir.CompareInt2D(float4::LEFT))
		{

			int RamDir = GameEngineRandom::MainRandom.RandomInt(0, 4);
			if (RamDir == 0)
			{
				Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.f);
				Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);

				StartDirList_.push_back(float4::RIGHT);
				DirList_.push_back(Dir);
			}
			else
			{
				Dir.x = GameEngineRandom::MainRandom.RandomFloat(-1.f, 0.f);
				Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);

				StartDirList_.push_back(float4::LEFT);
				DirList_.push_back(Dir);
			}

		}
		else if (_Dir.CompareInt2D(float4::UP))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.7f, 0.7f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.0f);

			StartDirList_.push_back(float4::UP);

			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::DOWN))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.7f, 0.7f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.f, 0.f);
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

void GrimmHitEffect::SetTexWhite()
{
}

void GrimmHitEffect::SetisImpact(bool _b)
{
}
