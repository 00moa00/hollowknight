#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightDoubleJumpEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightDoubleJumpEffect();
	~KnightDoubleJumpEffect();

	// delete Function
	KnightDoubleJumpEffect(const KnightDoubleJumpEffect& _Other) = delete;
	KnightDoubleJumpEffect(KnightDoubleJumpEffect&& _Other) noexcept = delete;
	KnightDoubleJumpEffect& operator=(const KnightDoubleJumpEffect& _Other) = delete;
	KnightDoubleJumpEffect& operator=(KnightDoubleJumpEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void SetEffectOn();
};

