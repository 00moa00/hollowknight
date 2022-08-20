#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightSmallLightEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightSmallLightEffect();
	~KnightSmallLightEffect();

	// delete Function
	KnightSmallLightEffect(const KnightSmallLightEffect& _Other) = delete;
	KnightSmallLightEffect(KnightSmallLightEffect&& _Other) noexcept = delete;
	KnightSmallLightEffect& operator=(const KnightSmallLightEffect& _Other) = delete;
	KnightSmallLightEffect& operator=(KnightSmallLightEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

