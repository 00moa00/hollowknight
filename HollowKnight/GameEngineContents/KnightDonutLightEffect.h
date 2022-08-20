#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightDonutLightEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightDonutLightEffect();
	~KnightDonutLightEffect();

	// delete Function
	KnightDonutLightEffect(const KnightDonutLightEffect& _Other) = delete;
	KnightDonutLightEffect(KnightDonutLightEffect&& _Other) noexcept = delete;
	KnightDonutLightEffect& operator=(const KnightDonutLightEffect& _Other) = delete;
	KnightDonutLightEffect& operator=(KnightDonutLightEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

