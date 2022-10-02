#pragma once
#include "MasterEffect.h"

// 설명 : 집중했을때
class KnightBurstEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightBurstEffect();
	~KnightBurstEffect();

	// delete Function
	KnightBurstEffect(const KnightBurstEffect& _Other) = delete;
	KnightBurstEffect(KnightBurstEffect&& _Other) noexcept = delete;
	KnightBurstEffect& operator=(const KnightBurstEffect& _Other) = delete;
	KnightBurstEffect& operator=(KnightBurstEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

