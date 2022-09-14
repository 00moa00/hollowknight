#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightMainLightEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightMainLightEffect();
	~KnightMainLightEffect();

	// delete Function
	KnightMainLightEffect(const KnightMainLightEffect& _Other) = delete;
	KnightMainLightEffect(KnightMainLightEffect&& _Other) noexcept = delete;
	KnightMainLightEffect& operator=(const KnightMainLightEffect& _Other) = delete;
	KnightMainLightEffect& operator=(KnightMainLightEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

