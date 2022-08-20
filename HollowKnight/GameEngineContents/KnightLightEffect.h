#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightLightEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightLightEffect();
	~KnightLightEffect();

	// delete Function
	KnightLightEffect(const KnightLightEffect& _Other) = delete;
	KnightLightEffect(KnightLightEffect&& _Other) noexcept = delete;
	KnightLightEffect& operator=(const KnightLightEffect& _Other) = delete;
	KnightLightEffect& operator=(KnightLightEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

