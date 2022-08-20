#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class SideDarkEffect : public MasterEffect
{
public:
	// constrcuter destructer
	SideDarkEffect();
	~SideDarkEffect();

	// delete Function
	SideDarkEffect(const SideDarkEffect& _Other) = delete;
	SideDarkEffect(SideDarkEffect&& _Other) noexcept = delete;
	SideDarkEffect& operator=(const SideDarkEffect& _Other) = delete;
	SideDarkEffect& operator=(SideDarkEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

