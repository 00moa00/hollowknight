#pragma once
#include "MasterNPC.h"

// Ό³Έν :
class Brummm : public MasterNPC
{
public:
	// constrcuter destructer
	Brummm();
	~Brummm();

	// delete Function
	Brummm(const Brummm& _Other) = delete;
	Brummm(Brummm&& _Other) noexcept = delete;
	Brummm& operator=(const Brummm& _Other) = delete;
	Brummm& operator=(Brummm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


};

