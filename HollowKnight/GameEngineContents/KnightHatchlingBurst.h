#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightHatchlingBurst : public MasterEffect
{
public:
	// constrcuter destructer
	KnightHatchlingBurst();
	~KnightHatchlingBurst();

	// delete Function
	KnightHatchlingBurst(const KnightHatchlingBurst& _Other) = delete;
	KnightHatchlingBurst(KnightHatchlingBurst&& _Other) noexcept = delete;
	KnightHatchlingBurst& operator=(const KnightHatchlingBurst& _Other) = delete;
	KnightHatchlingBurst& operator=(KnightHatchlingBurst&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void EffectOn();
};

