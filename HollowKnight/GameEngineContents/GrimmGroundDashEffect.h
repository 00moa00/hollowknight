#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmGroundDashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmGroundDashEffect();
	~GrimmGroundDashEffect();

	// delete Function
	GrimmGroundDashEffect(const GrimmGroundDashEffect& _Other) = delete;
	GrimmGroundDashEffect(GrimmGroundDashEffect&& _Other) noexcept = delete;
	GrimmGroundDashEffect& operator=(const GrimmGroundDashEffect& _Other) = delete;
	GrimmGroundDashEffect& operator=(GrimmGroundDashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

