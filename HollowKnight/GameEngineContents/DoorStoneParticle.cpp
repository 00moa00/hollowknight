#include "PreCompile.h"
#include "DoorStoneParticle.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "HollowKnightLevel.h"

DoorStoneParticle::DoorStoneParticle() 
{
}

DoorStoneParticle::~DoorStoneParticle() 
{
}

void DoorStoneParticle::Start()
{
	for (int i = 0; i < 25; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 7);

		if (RamdomIndex == 0)
		{
			ParticleList_.back()->SetTexture("rock_01.png");
			ParticleList_.back()->GetTransform().SetWorldScale({23, 18});
		}

		else if (RamdomIndex == 1)
		{
			ParticleList_.back()->SetTexture("rock_01_b.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 43, 35 });

		}
		else if (RamdomIndex == 2)
		{
			ParticleList_.back()->SetTexture("rock_02.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 15, 16 });

		}
		else if (RamdomIndex == 3)
		{
			ParticleList_.back()->SetTexture("rock_02_b.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 32, 28 });

		}

		else if (RamdomIndex == 4)
		{
			ParticleList_.back()->SetTexture("rock_03.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 18, 14 });

		}

		else if (RamdomIndex == 5)
		{
			ParticleList_.back()->SetTexture("rock_03_b.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 30, 31 });

		}

		else if (RamdomIndex == 6)
		{
			ParticleList_.back()->SetTexture("rock_04.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 14, 13 });

		}

		else if (RamdomIndex == 7)
		{
			ParticleList_.back()->SetTexture("rock_04_b.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 36, 21 });

		}


		//ParticleList_.back()->SetScaleModeImage();
		isEndMove_.push_back(false);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-30.f, 30.f);
		ParticleList_.back()->GetTransform().SetWorldRotation({0,0,RamdomRo });
	}

	Speed_ = 1600.f;
}

void DoorStoneParticle::Update(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		if (isEndMove_[i] == true)
		{
			//ParticleList_[i]->Off();
		}
		else
		{
			isPixelDownCheck(_DeltaTime);

			if (InitDir_[i].CompareInt2D(float4::RIGHT))
			{
				DirList_[i].x += 0.0001f;
				DirList_[i].y -= 0.01f;

				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}

			if (InitDir_[i].CompareInt2D(float4::LEFT))
			{
				DirList_[i].x -= 0.0001f;

				DirList_[i].y -= 0.01f;
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}
	}
}

void DoorStoneParticle::isPixelDownCheck(float _DeltaTime)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 DowmPos = { ParticleList_[i]->GetTransform().GetWorldPosition().x ,
		-(ParticleList_[i]->GetTransform().GetWorldPosition().y - ((ParticleList_[i]->GetTransform().GetWorldScale().y / 3))) };

		float4 UpColor = GetLevel<HollowKnightLevel>()->GetMasterMap()->GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(DowmPos.ix(), DowmPos.iy());
		if (UpColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			if (isEndMove_[i] == false)
			{
				isEndMove_[i] = true;
			}
		}
		else
		{
		}
	}
}

void DoorStoneParticle::SetDir(float4 _Dir)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Dir;
		_Dir.Normalize();

		if (_Dir.x > 0.f)
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 0.4f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.6f, 0.2f);

			DirList_.push_back(Dir);
			InitDir_.push_back(float4::RIGHT);
		}

		else if (_Dir.x < 0.f)
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.4f, 0.f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.6f, 0.2f);

			DirList_.push_back(Dir);
			InitDir_.push_back(float4::LEFT);
		}

		else
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 0.f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.6f, 0.3f);

			DirList_.push_back(Dir);
			InitDir_.push_back(float4::RIGHT);

		}

	}
}
