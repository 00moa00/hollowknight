#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MasterActor.h"
#include "MonsterHitParticle.h"
#include "MonsterHitPuffEffect.h"

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

	int HitParticleCount_;
	int HitParticlePuffCount_;


	std::vector<MonsterHitParticle*>MonsterHitParticleList_;
	std::vector<MonsterHitPuffEffect*>MonsterHitPuffEffectList_;

protected:
	void SetMonsterDirection();
	void SetDirRendererXScale();


public:
	//================================
	//    Setter
	//================================


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



};

