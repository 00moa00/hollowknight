#pragma once

// Ό³Έν :
class HealthBugPlant
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

private:

};

