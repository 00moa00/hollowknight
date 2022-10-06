#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MasterActor.h"
#include "MonsterHitParticle.h"
#include "MonsterHitPuffEffect.h"
#include "MonsterDeathPuffParticle.h"
#include "MonsterHitOrangeLight.h"
#include "GrimmHitEffect.h"

enum class MonsterType
{
	Normal,
	Spike
};

// Ό³Έν :
class Monster : public MasterActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

public:
	//void Start() override;
	//void Update(float _DeltaTime) {}
	//void End() {}

	virtual void SetMonsterHit(int _Damage, float4 _StunDir, float4 _KnightDir) {};

private:

	bool isMonsterDeath_;

	int AllHP_;
	int CurHp_;

	int DropGeo_;

	int HitParticleCount_;
	int HitParticlePuffCount_;
	int HitLightCount_;

	MonsterType MonsterType_;

	MonsterDeathPuffParticle* MonsterDeathPuffParticle_;

	std::vector<MonsterHitParticle*>MonsterHitParticleList_;
	std::vector<MonsterHitPuffEffect*>MonsterHitPuffEffectList_;
	std::vector<MonsterHitOrangeLight*> MonsterHitOrangeLightList_;
	std::vector<GrimmHitEffect*> GrimmHitEffectList_;

protected:
	void SetMonsterDirection();
	void SetDirRendererXScale();


public:
	//================================
	//    Setter
	//================================



	void CreateMonsterHitLight(int _i)
	{
		for (int i = 0; i < _i; ++i)
		{
			MonsterHitOrangeLightList_.push_back(GetLevel()->CreateActor<MonsterHitOrangeLight>());
			MonsterHitOrangeLightList_.back()->GetTransform().SetWorldScale({GetRenderer()->GetTransform().GetWorldScale().x * 2.5f, GetRenderer()->GetTransform().GetWorldScale().x * 2.5f });
			MonsterHitOrangeLightList_.back()->Off();
		}
	}

	void SetMonsterHitLightOn()
	{
		if (HitLightCount_ < MonsterHitOrangeLightList_.size())
		{
			MonsterHitOrangeLightList_[HitLightCount_]->On();
			MonsterHitOrangeLightList_[HitLightCount_]->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x , GetTransform().GetWorldPosition().y  });

			++HitLightCount_;
		}
	}


	void CreateMonsterDeathPuffParticle();

	void SetMonsterDeathPuffParticleOn();

	void CreateMonsterHitPuffParticle(int _i)
	{
		for (int i = 0; i < _i; ++i)
		{
			MonsterHitPuffEffectList_.push_back(GetLevel()->CreateActor<MonsterHitPuffEffect>());
			//MonsterHitParticleList_.back()->SetParent(this);
			MonsterHitPuffEffectList_.back()->Off();
		}
	}

	void SetCreateMonsterHitPuffParticleOn(float4 _Dir, float4 _Scale)
	{
		if (HitParticlePuffCount_ < MonsterHitParticleList_.size())
		{
			MonsterHitPuffEffectList_[HitParticlePuffCount_]->On();
			MonsterHitPuffEffectList_[HitParticlePuffCount_]->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -50 });
			MonsterHitPuffEffectList_[HitParticlePuffCount_]->SetDir(_Dir);

			if (_Dir.CompareInt2D(float4::RIGHT))
			{
				MonsterHitPuffEffectList_[HitParticlePuffCount_]->GetTransform().SetWorldMove({
					_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::LEFT))
			{
				MonsterHitPuffEffectList_[HitParticlePuffCount_]->GetTransform().SetWorldMove({
					-_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::UP))
			{
				MonsterHitPuffEffectList_[HitParticlePuffCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::DOWN))
			{
				MonsterHitPuffEffectList_[HitParticlePuffCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}


			++HitParticlePuffCount_;
		}
	}

	void CreateMonsterHitParticle(int _i)
	{
		for (int i = 0; i < _i ; ++i)
		{
			MonsterHitParticleList_.push_back(GetLevel()->CreateActor<MonsterHitParticle>());
			//MonsterHitParticleList_.back()->SetParent(this);
			MonsterHitParticleList_.back()->Off();
		}
	}

	void CreateGrimmHitParticle(int _i)
	{
		for (int i = 0; i < _i; ++i)
		{
			GrimmHitEffectList_.push_back(GetLevel()->CreateActor<GrimmHitEffect>());
			//MonsterHitParticleList_.back()->SetParent(this);
			GrimmHitEffectList_.back()->Off();
		}
	}

	void SetMonsterHitEffectWhiteTex()
	{
		for (int i = 0; i < MonsterHitParticleList_.size(); ++i)
		{
			MonsterHitParticleList_[i]->SetTexWhite();
		}
	}

	void SetMonsterHitEffectisImpact()
	{
		for (int i = 0; i < MonsterHitParticleList_.size(); ++i)
		{
			MonsterHitParticleList_[i]->SetisImpact(false);
		}
	}

	void SetCreateMonsterHitParticleOn(float4 _Dir, float4 _Scale)
	{
		if (HitParticleCount_ < MonsterHitParticleList_.size())
		{
			MonsterHitParticleList_[HitParticleCount_]->On();
			MonsterHitParticleList_[HitParticleCount_]->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -50});
			MonsterHitParticleList_[HitParticleCount_]->SetDir(_Dir);

			if (_Dir.CompareInt2D(float4::RIGHT))
			{
				MonsterHitParticleList_[HitParticleCount_]->GetTransform().SetWorldMove({
					_Scale.x/4,
					_Scale.y/4, });
			}
			else if (_Dir.CompareInt2D(float4::LEFT))
			{
				MonsterHitParticleList_[HitParticleCount_]->GetTransform().SetWorldMove({
					-_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::UP))
			{
				MonsterHitParticleList_[HitParticleCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::DOWN))
			{
				MonsterHitParticleList_[HitParticleCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}


			++HitParticleCount_;
		}
	}

	void SetCreateGrimmHitParticleOn(float4 _Dir, float4 _Scale)
	{
		if (HitParticleCount_ < GrimmHitEffectList_.size())
		{
			GrimmHitEffectList_[HitParticleCount_]->On();
			GrimmHitEffectList_[HitParticleCount_]->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -50 });
			GrimmHitEffectList_[HitParticleCount_]->SetDir(_Dir);

			if (_Dir.CompareInt2D(float4::RIGHT))
			{
				GrimmHitEffectList_[HitParticleCount_]->GetTransform().SetWorldMove({
					_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::LEFT))
			{
				GrimmHitEffectList_[HitParticleCount_]->GetTransform().SetWorldMove({
					-_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::UP))
			{
				GrimmHitEffectList_[HitParticleCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::DOWN))
			{
				GrimmHitEffectList_[HitParticleCount_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}


			++HitParticleCount_;
		}
	}


	void SubHP(int _i)
	{
		CurHp_ -= _i;

		if (CurHp_ == 0)
		{
			isMonsterDeath_ = true;
		}
	}

	void SetHP(int _i)
	{
		AllHP_ = _i;
		CurHp_ = _i;

	}

	void SetMonsterType(MonsterType _MonsterType)
	{
		MonsterType_ = _MonsterType;
	}

	void SetDropGeo(int _Count)
	{
		DropGeo_ = _Count;
	}


	//================================
	//     Getter
	//================================

	bool GetisMonsterDeath()
	{
		return isMonsterDeath_;
	}

	int GetHP()
	{
		return CurHp_;
	}

	MonsterType GetMonsterType()
	{
		return MonsterType_;
	}

	int GetDropGeo()
	{
		return DropGeo_;
	}

};

