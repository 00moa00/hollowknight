#pragma once
#include "Monster.h"

// Ό³Έν :
class Buzzer : public Monster
{
public:
	// constrcuter destructer
	Buzzer();
	~Buzzer();

	// delete Function
	Buzzer(const Buzzer& _Other) = delete;
	Buzzer(Buzzer&& _Other) noexcept = delete;
	Buzzer& operator=(const Buzzer& _Other) = delete;
	Buzzer& operator=(Buzzer&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMonsterHit(int _Damage, float4 _StunDir, float4 _KnightDir) override;

private:
	bool isTurnEnd_;
	bool isDeathEnd_;
	bool isStartleEnd_;


	float BuzzerKnockbackTimer_;
	float BuzzerFreeFlyTimer_;

	GameEngineStateManager BuzzerManager_;

private:
	void DirectionCheck();

	void BuzzerStatleStart(const StateInfo& _Info);
	void BuzzerStatleUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerStatleEnd(const StateInfo& _Info);

	void BuzzerIdleStart(const StateInfo& _Info);
	void BuzzerIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerIdleEnd(const StateInfo& _Info);

	void BuzzerDeathStart(const StateInfo& _Info);
	void BuzzerDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerDeathEnd(const StateInfo& _Info);

	void BuzzerFlyStart(const StateInfo& _Info);
	void BuzzerFlyUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerFlyEnd(const StateInfo& _Info);

	void BuzzerFreeFlyStart(const StateInfo& _Info);
	void BuzzerFreeFlyUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerFreeFlyEnd(const StateInfo& _Info);

	void BuzzerHitStart(const StateInfo& _Info);
	void BuzzerHitUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerHitEnd(const StateInfo& _Info);

	void BuzzerTurnStart(const StateInfo& _Info);
	void BuzzerTurnUpdate(float _DeltaTime, const StateInfo& _Info);
	void BuzzerTurnEnd(const StateInfo& _Info);

	//================================
	//    Bind  Pointer
	//================================
	bool ThisVSKnihgtCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

