#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightCastImpactEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightCastImpactEffect();
	~KnightCastImpactEffect();

	// delete Function
	KnightCastImpactEffect(const KnightCastImpactEffect& _Other) = delete;
	KnightCastImpactEffect(KnightCastImpactEffect&& _Other) noexcept = delete;
	KnightCastImpactEffect& operator=(const KnightCastImpactEffect& _Other) = delete;
	KnightCastImpactEffect& operator=(KnightCastImpactEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

