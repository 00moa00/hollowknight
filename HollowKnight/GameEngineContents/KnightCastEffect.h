#pragma once
#include "MasterEffect.h"

// 설명 : 포 날릴때 플레이어 이펙트 
class KnightCastEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightCastEffect();
	~KnightCastEffect();

	// delete Function
	KnightCastEffect(const KnightCastEffect& _Other) = delete;
	KnightCastEffect(KnightCastEffect&& _Other) noexcept = delete;
	KnightCastEffect& operator=(const KnightCastEffect& _Other) = delete;
	KnightCastEffect& operator=(KnightCastEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Dir_;

public:
	void EffectOn(float4 _Dir);
};

