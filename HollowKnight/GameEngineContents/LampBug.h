#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class LampBug : public MasterEffect
{
public:
	// constrcuter destructer
	LampBug();
	~LampBug();

	// delete Function
	LampBug(const LampBug& _Other) = delete;
	LampBug(LampBug&& _Other) noexcept = delete;
	LampBug& operator=(const LampBug& _Other) = delete;
	LampBug& operator=(LampBug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Dir_;
	float4 LimitMoveSize_;
	float4 PivotPos_;

	float Alpha_;

public:
	void SetLimitMove(float4 _CurrentPos, float4 _LimitSize);

};

