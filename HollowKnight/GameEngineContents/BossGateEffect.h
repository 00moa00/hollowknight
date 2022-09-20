#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class BossGateEffect : public MasterEffect
{
public:
	// constrcuter destructer
	BossGateEffect();
	~BossGateEffect();

	// delete Function
	BossGateEffect(const BossGateEffect& _Other) = delete;
	BossGateEffect(BossGateEffect&& _Other) noexcept = delete;
	BossGateEffect& operator=(const BossGateEffect& _Other) = delete;
	BossGateEffect& operator=(BossGateEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

