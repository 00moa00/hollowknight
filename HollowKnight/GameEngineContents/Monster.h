#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MasterActor.h"

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

	virtual void SetMonsterHit(int _Damage, float4 _StunDir) {};
private:

	bool isMonsterDeath_;

	int AllHP_;
	int CurHp_;


protected:
	void SetMonsterDirection();



public:
	//================================
	//    Setter
	//================================



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





};

