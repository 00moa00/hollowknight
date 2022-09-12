#pragma once
#include "MasterUI.h"

// Ό³Έν :
class VesselFrame : public MasterUI
{
public:
	// constrcuter destructer
	VesselFrame();
	~VesselFrame();

	// delete Function
	VesselFrame(const VesselFrame& _Other) = delete;
	VesselFrame(VesselFrame&& _Other) noexcept = delete;
	VesselFrame& operator=(const VesselFrame& _Other) = delete;
	VesselFrame& operator=(VesselFrame&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

public:
	void SetIdleAnimation();

};

