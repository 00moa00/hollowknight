#pragma once
#include "MasterObject.h"
// Ό³Έν :
class Bench : public MasterObject
{
public:
	// constrcuter destructer
	Bench();
	~Bench();

	// delete Function
	Bench(const Bench& _Other) = delete;
	Bench(Bench&& _Other) noexcept = delete;
	Bench& operator=(const Bench& _Other) = delete;
	Bench& operator=(Bench&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

