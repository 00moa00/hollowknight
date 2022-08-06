#pragma once
#include "Monster.h"

// Ό³Έν :
class Vengefly : public Monster
{
public:
	// constrcuter destructer
	Vengefly();
	~Vengefly();

	// delete Function
	Vengefly(const Vengefly& _Other) = delete;
	Vengefly(Vengefly&& _Other) noexcept = delete;
	Vengefly& operator=(const Vengefly& _Other) = delete;
	Vengefly& operator=(Vengefly&& _Other) noexcept = delete;

protected:

private:
	GameEngineStateManager VengeflyManager_;

private:
	//================================
	//    Bind State
	//================================
	void VengeflyStillStart(const StateInfo& _Info);
	void VengeflyStillUpdate(float _DeltaTime, const StateInfo& _Info);


	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

};

