#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightInvincibilityEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightInvincibilityEffect();
	~KnightInvincibilityEffect();

	// delete Function
	KnightInvincibilityEffect(const KnightInvincibilityEffect& _Other) = delete;
	KnightInvincibilityEffect(KnightInvincibilityEffect&& _Other) noexcept = delete;
	KnightInvincibilityEffect& operator=(const KnightInvincibilityEffect& _Other) = delete;
	KnightInvincibilityEffect& operator=(KnightInvincibilityEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void EffectOn();
	void EffectOff();

};

