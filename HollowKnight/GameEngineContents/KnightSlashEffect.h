#pragma once
#include "MasterEffect.h"
#include "KnightSlashAttackEffect.h"

// Ό³Έν :
class KnightSlashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightSlashEffect();
	~KnightSlashEffect();

	// delete Function
	KnightSlashEffect(const KnightSlashEffect& _Other) = delete;
	KnightSlashEffect(KnightSlashEffect&& _Other) noexcept = delete;
	KnightSlashEffect& operator=(const KnightSlashEffect& _Other) = delete;
	KnightSlashEffect& operator=(KnightSlashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isSlashEnd_;

	bool isColl_;

	float4 Dir_;

	GameEngineStateManager KnightSlashEffectManager_;

	KnightSlashAttackEffect* KnightSlashAttackEffect_;
private:

	//================================
	//    Bind State
	//================================
	void SlashIdleStart(const StateInfo& _Info);
	void SlashIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlashIdleEnd(const StateInfo& _Info);

	void SlashHitEnemyStart(const StateInfo& _Info);
	void SlashHitEnemyUpdate(float _DeltaTime, const StateInfo& _Info);
	void SlashHitEnemyEnd(const StateInfo& _Info);



public:
	bool GetisColl()
	{
		return isColl_;
	}

	float4 GetDir()
	{
		return Dir_;
	}

	void SetColl()
	{
		isColl_ = true;
		KnightSlashEffectManager_.ChangeState("HIT_ENEMY");

	}
	
	void SetAnimationSlash();
	void SetAnimationDoubleSlash();
	void SetAnimationUpSlash();
	void SetAnimationDownSlash();
	void SetAnimationStill();


	bool EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool EffectVSObjectCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

	bool EffectVSWallFalseCheckCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

