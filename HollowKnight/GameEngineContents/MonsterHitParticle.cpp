#include "PreCompile.h"
#include "MonsterHitParticle.h"
#include "HollowKnightLevel.h"

MonsterHitParticle::MonsterHitParticle() 
	:
	Scale_(1.0f),
	Speed_(0.0f)
{
}

MonsterHitParticle::~MonsterHitParticle() 
{
}

void MonsterHitParticle::Start()
{
	Speed_ = 550.f;

	for (int i = 0; i < 10; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 2);
		ParticleList_.back()->SetTexture("white_hit_particle_Orange.png", RamdomIndex);
		ParticleList_.back()->ScaleToCutTexture(RamdomIndex);

		ParticleList_.back()->GetTransform().SetWorldScale({
		ParticleList_.back()->GetTransform().GetLocalScale().x + GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f)
		,	ParticleList_.back()->GetTransform().GetLocalScale().y + GameEngineRandom::MainRandom.RandomFloat(-10.f, 10.f) }
		);

		ParticleList_.back()->CreateFrameAnimationCutTexture("IDLE", FrameAnimation_DESC("white_hit_particle_Orange.png", RamdomIndex, RamdomIndex, 0.100f, false));
		ParticleList_.back()->CreateFrameAnimationCutTexture("SHOT_ANIMATION", FrameAnimation_DESC("Projectiles_shot_impact0001-Sheet.png", 0, 6, 0.100f, false));
		ParticleList_.back()->ChangeFrameAnimation("IDLE");
		InitScale_.push_back(ParticleList_.back()->GetTransform().GetLocalScale());
		//ParticleList_.back()->AnimationBindEnd("SHOT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		//	{
		//		ParticleList_.back()->Off();
		//	});

		isEndMove_.push_back(false);
	}

	//Off();
}

void MonsterHitParticle::Update(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		if (StartDirList_[i].CompareInt2D(float4::RIGHT))
		{
			DirList_[i].x += 0.0001f;
			DirList_[i].y -= 0.01f;

			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (StartDirList_[i].CompareInt2D(float4::LEFT))
		{
			DirList_[i].x -= 0.0001f;

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
				DirList_[i].x += 0.0001f;
			}

			else
			{
				DirList_[i].x -= 0.0001f;
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
				DirList_[i].x += 0.0001f;
			}

			else
			{
				DirList_[i].x -= 0.0001f;
			}

			DirList_[i].y += -0.01f;
			if (isEndMove_[i] == false)
			{
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}

		if (isEndMove_[i] == true)
		{

			if (ParticleList_[i]->GetCurFrameAnimation()->GetFrameAnimationDesc().GetCurFrame() == 6)
			{
				ParticleList_[i]->Off();
			}
		}

		Scale_ -= 0.12f * _DeltaTime;
		if (Scale_ <= 0.f)
		{
			ParticleList_[i]->Off();
			Scale_ = 0.f;
			this->Off();
		}
		if (isEndMove_[i] == false)
		{
			ParticleList_[i]->GetTransform().SetWorldScale(InitScale_[i] * Scale_);

		}
	}

	isPixelCheck(_DeltaTime);
}

void MonsterHitParticle::isPixelCheck(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 DowmPos = { ParticleList_[i] -> GetTransform().GetWorldPosition().x ,
		-(ParticleList_[i]->GetTransform().GetWorldPosition().y - ((ParticleList_[i] ->GetTransform().GetWorldScale().y/3 ))) };

		float4 UpColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(DowmPos.ix(), DowmPos.iy());
		if (UpColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			//int i = 0;
			if (isEndMove_[i] == false && Scale_ > 0.f)
			{
				int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 7);


				if (RamdomIndex == 1)
				{
					ParticleList_[i]->ChangeFrameAnimation("SHOT_ANIMATION");
					ParticleList_[i]->ScaleToCutTexture(0);
					ParticleList_[i]->GetTransform().SetWorldScale({
	ParticleList_[i]->GetTransform().GetLocalScale().x + GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f)
	,	ParticleList_[i]->GetTransform().GetLocalScale().y + GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f) }
					);
					isEndMove_[i] = true;
				}

				else
				{

				}

			}
		}
		else
		{
			//	SetisUpBlock(false);
		}

	}



	
}

void MonsterHitParticle::SetDir(float4 _Dir)
{
	for (int i = 0; i < ParticleList_.size() ; ++i)
	{
		float4 Dir;

		if (_Dir.CompareInt2D(float4::RIGHT))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.0f);
			Dir.y= GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);
			
			StartDirList_.push_back(float4::RIGHT);
			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::LEFT))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-1.f, 0.f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);

			StartDirList_.push_back(float4::LEFT);
			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::UP))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(0.f, 1.0f);

			StartDirList_.push_back(float4::UP);

			DirList_.push_back(Dir);
		}
		else if (_Dir.CompareInt2D(float4::DOWN))
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-1.0f, 1.0f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-1.f, 0.f);
			StartDirList_.push_back(float4::DOWN);

			DirList_.push_back(Dir);
		}

		InitDir_.push_back(Dir);
	}
}

