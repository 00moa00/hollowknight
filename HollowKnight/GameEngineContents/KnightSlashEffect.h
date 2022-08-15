#pragma once
#include "MasterEffect.h"

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
	GameEngineStateManager KnightSlashEffectManager_;

private:

	//================================
	//    Bind State
	//================================


public:

	void SetAnimationSlash();
	void SetAnimationDoubleSlash();
	void SetAnimationUpSlash();
	void SetAnimationDownSlash();
	void SetAnimationStill();

	bool EffectVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

