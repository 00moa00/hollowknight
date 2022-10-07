#pragma once
#include "MasterObject.h"

// Ό³Έν :
class HealthBugPlant2 : public MasterObject
{
public:
	// constrcuter destructer
	HealthBugPlant2();
	~HealthBugPlant2();

	// delete Function
	HealthBugPlant2(const HealthBugPlant2& _Other) = delete;
	HealthBugPlant2(HealthBugPlant2&& _Other) noexcept = delete;
	HealthBugPlant2& operator=(const HealthBugPlant2& _Other) = delete;
	HealthBugPlant2& operator=(HealthBugPlant2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetKnightCollision() override;

public:
	void SetScaleXNegative();

};

