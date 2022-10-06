#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightBurstPlusEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightBurstPlusEffect();
	~KnightBurstPlusEffect();

	// delete Function
	KnightBurstPlusEffect(const KnightBurstPlusEffect& _Other) = delete;
	KnightBurstPlusEffect(KnightBurstPlusEffect&& _Other) noexcept = delete;
	KnightBurstPlusEffect& operator=(const KnightBurstPlusEffect& _Other) = delete;
	KnightBurstPlusEffect& operator=(KnightBurstPlusEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


public:
	void EffectOn();
};

