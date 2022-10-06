#include "PreCompile.h"
#include "LargeStoneParticle.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "HollowKnightLevel.h"


LargeStoneParticle::LargeStoneParticle() 
	:
	Speed_(0.f)
{
}

LargeStoneParticle::~LargeStoneParticle() 
{
}

void LargeStoneParticle::Start()
{
	for (int i = 0; i < 3; ++i)
	{
		ParticleList_.push_back(CreateComponent<GameEngineTextureRenderer>());
		int RamdomIndex = GameEngineRandom::MainRandom.RandomInt(0, 9);

		float ScaleSize = 0.5f;

		if (RamdomIndex == 0)
		{
			ParticleList_.back()->SetTexture("boss_door_chunks_0003_1.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 108 * ScaleSize, 222 * ScaleSize });
		}

		else if (RamdomIndex == 1)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_02.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 124 * ScaleSize, 116 * ScaleSize });

		}
		else if (RamdomIndex == 2)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_03.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 136 * ScaleSize, 169 * ScaleSize });

		}
		else if (RamdomIndex == 3)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_04.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 246 * ScaleSize, 338 * ScaleSize });

		}

		else if (RamdomIndex == 4)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_05.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 229 * ScaleSize, 353 * ScaleSize });

		}

		else if (RamdomIndex == 5)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_06.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 258 * ScaleSize, 410 * ScaleSize });

		}

		else if (RamdomIndex == 6)
		{
			ParticleList_.back()->SetTexture("break_door_large_piece_07.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 182 * ScaleSize, 235 * ScaleSize });

		}

		else if (RamdomIndex == 7)
		{
			ParticleList_.back()->SetTexture("Tute Great Door_additional_destruction_0000_a.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 103 * ScaleSize, 121 * ScaleSize });

		}

		else if (RamdomIndex == 8)
		{
			ParticleList_.back()->SetTexture("Tute Great Door_additional_destruction_0001_a.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 154 * ScaleSize, 159 * ScaleSize });

		}


		else if (RamdomIndex == 9)
		{
			ParticleList_.back()->SetTexture("Tute Great Door_additional_destruction_0002_a.png");
			ParticleList_.back()->GetTransform().SetWorldScale({ 154 * ScaleSize, 159 * ScaleSize });

		}



		//ParticleList_.back()->SetScaleModeImage();
		isEndMove_.push_back(false);

		float RamdomRo = GameEngineRandom::MainRandom.RandomFloat(-30.f, 30.f);
		ParticleList_.back()->GetTransform().SetWorldRotation({ 0,0,RamdomRo });
	}

	Speed_ = 2700.f;
}

void LargeStoneParticle::Update(float _DeltaTime)
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
				DirList_[i].x += 0.0001f * _DeltaTime * 100.f;
				DirList_[i].y -= 0.01f * _DeltaTime * 100.f;

				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}

			if (InitDir_[i].CompareInt2D(float4::LEFT))
			{
				DirList_[i].x -= 0.0001f * _DeltaTime * 100.f;

				DirList_[i].y -= 0.01f * _DeltaTime * 100.f;
				ParticleList_[i]->GetTransform().SetWorldMove(DirList_[i] * Speed_ * _DeltaTime);
			}
		}
	}
}

void LargeStoneParticle::isPixelDownCheck(float _DeltaTime)
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

void LargeStoneParticle::SetDir(float4 _Dir)
{
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		float4 Dir;
		_Dir.Normalize();

		if (_Dir.x > 0.f)
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(0.f, 0.4f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.6f, 0.3f);

			DirList_.push_back(Dir);
			InitDir_.push_back(float4::RIGHT);
		}

		else if (_Dir.x < 0.f)
		{
			Dir.x = GameEngineRandom::MainRandom.RandomFloat(-0.4f, 0.f);
			Dir.y = GameEngineRandom::MainRandom.RandomFloat(-0.6f, 0.3f);

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

void LargeStoneParticle::SetRamPos(float MinY, float MaxY)
{
	float RamdomPosY = GameEngineRandom::MainRandom.RandomFloat(MinY, MaxY);
	for (int i = 0; i < ParticleList_.size(); ++i)
	{
		ParticleList_[i]->GetTransform().SetWorldMove({ 0,RamdomPosY });
	}
}
