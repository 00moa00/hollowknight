#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightJumpDustEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightJumpDustEffect();
	~KnightJumpDustEffect();

	// delete Function
	KnightJumpDustEffect(const KnightJumpDustEffect& _Other) = delete;
	KnightJumpDustEffect(KnightJumpDustEffect&& _Other) noexcept = delete;
	KnightJumpDustEffect& operator=(const KnightJumpDustEffect& _Other) = delete;
	KnightJumpDustEffect& operator=(KnightJumpDustEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void EffectOn(float4 _Dir);
};

