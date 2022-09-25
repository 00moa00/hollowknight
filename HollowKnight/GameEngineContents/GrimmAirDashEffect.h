#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmAirDashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmAirDashEffect();
	~GrimmAirDashEffect();

	// delete Function
	GrimmAirDashEffect(const GrimmAirDashEffect& _Other) = delete;
	GrimmAirDashEffect(GrimmAirDashEffect&& _Other) noexcept = delete;
	GrimmAirDashEffect& operator=(const GrimmAirDashEffect& _Other) = delete;
	GrimmAirDashEffect& operator=(GrimmAirDashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

