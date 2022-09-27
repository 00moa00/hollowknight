#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MasterActor.h"
#include "MonsterHitParticle.h"

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

	int Count_;

	std::vector<MonsterHitParticle*>MonsterHitParticleList_;

protected:
	void SetMonsterDirection();
	void SetDirRendererXScale();


public:
	//================================
	//    Setter
	//================================

	void CreateMonsterHitParticle(int _i)
	{
		for (int i = 0; i < _i ; ++i)
		{
			MonsterHitParticleList_.push_back(GetLevel()->CreateActor<MonsterHitParticle>());
			//MonsterHitParticleList_.back()->SetParent(this);
			MonsterHitParticleList_.back()->Off();
		}
	}

	void SetCreateMonsterHitParticleOn(float4 _Dir, float4 _Scale)
	{
		if (Count_ < MonsterHitParticleList_.size())
		{
			MonsterHitParticleList_[Count_]->On();
			MonsterHitParticleList_[Count_]->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, -50});
			MonsterHitParticleList_[Count_]->SetDir(_Dir);

			if (_Dir.CompareInt2D(float4::RIGHT))
			{
				MonsterHitParticleList_[Count_]->GetTransform().SetWorldMove({
					_Scale.x/4,
					_Scale.y/4, });
			}
			else if (_Dir.CompareInt2D(float4::LEFT))
			{
				MonsterHitParticleList_[Count_]->GetTransform().SetWorldMove({
					-_Scale.x / 4,
					_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::UP))
			{
				MonsterHitParticleList_[Count_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}
			else if (_Dir.CompareInt2D(float4::DOWN))
			{
				MonsterHitParticleList_[Count_]->GetTransform().SetWorldMove({
					0,
					+_Scale.y / 4, });
			}


			++Count_;
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

