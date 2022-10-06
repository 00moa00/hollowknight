#pragma once
#include "MasterObject.h"


// Ό³Έν :
class HealthBugPlant : public MasterObject
{
public:
	// constrcuter destructer
	HealthBugPlant();
	~HealthBugPlant();

	// delete Function
	HealthBugPlant(const HealthBugPlant& _Other) = delete;
	HealthBugPlant(HealthBugPlant&& _Other) noexcept = delete;
	HealthBugPlant& operator=(const HealthBugPlant& _Other) = delete;
	HealthBugPlant& operator=(HealthBugPlant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetKnightCollision() override;

private:

};

