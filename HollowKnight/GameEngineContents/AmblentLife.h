#pragma once
#include "MasterEffect.h"
#include "PerlinNoise.h"
// Ό³Έν :
class AmblentLife : public MasterEffect
{
public:
	// constrcuter destructer
	AmblentLife();
	~AmblentLife();

	// delete Function
	AmblentLife(const AmblentLife& _Other) = delete;
	AmblentLife(AmblentLife&& _Other) noexcept = delete;
	AmblentLife& operator=(const AmblentLife& _Other) = delete;
	AmblentLife& operator=(AmblentLife&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Dir_;
	float4 LimitMoveSize_;
	float4 PivotPos_;

public:
	void SetLimitMove(float4 _CurrentPos, float4 _LimitSize);
};

