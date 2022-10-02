#pragma once
#include "MasterNPC.h"


// Ό³Έν :
class Sycophant : public MasterNPC
{
public:
	// constrcuter destructer
	Sycophant();
	~Sycophant();

	// delete Function
	Sycophant(const Sycophant& _Other) = delete;
	Sycophant(Sycophant&& _Other) noexcept = delete;
	Sycophant& operator=(const Sycophant& _Other) = delete;
	Sycophant& operator=(Sycophant&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


};

