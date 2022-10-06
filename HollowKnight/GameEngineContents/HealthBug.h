#pragma once
#include "MasterObject.h"

// Ό³Έν :
class HealthBug : public MasterObject
{
public:
	// constrcuter destructer
	HealthBug();
	~HealthBug();

	// delete Function
	HealthBug(const HealthBug& _Other) = delete;
	HealthBug(HealthBug&& _Other) noexcept = delete;
	HealthBug& operator=(const HealthBug& _Other) = delete;
	HealthBug& operator=(HealthBug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void SetHitCollision() override;

	int HitCount_;

private:

};

