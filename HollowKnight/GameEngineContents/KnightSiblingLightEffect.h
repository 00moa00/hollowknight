#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightSiblingLightEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightSiblingLightEffect();
	~KnightSiblingLightEffect();

	// delete Function
	KnightSiblingLightEffect(const KnightSiblingLightEffect& _Other) = delete;
	KnightSiblingLightEffect(KnightSiblingLightEffect&& _Other) noexcept = delete;
	KnightSiblingLightEffect& operator=(const KnightSiblingLightEffect& _Other) = delete;
	KnightSiblingLightEffect& operator=(KnightSiblingLightEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

