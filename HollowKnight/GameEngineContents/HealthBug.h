#pragma once

// Ό³Έν :
class HealthBug
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

private:

};

