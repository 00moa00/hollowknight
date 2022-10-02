#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightDashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightDashEffect();
	~KnightDashEffect();

	// delete Function
	KnightDashEffect(const KnightDashEffect& _Other) = delete;
	KnightDashEffect(KnightDashEffect&& _Other) noexcept = delete;
	KnightDashEffect& operator=(const KnightDashEffect& _Other) = delete;
	KnightDashEffect& operator=(KnightDashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void EffectOn(float4 _Dir);
};

