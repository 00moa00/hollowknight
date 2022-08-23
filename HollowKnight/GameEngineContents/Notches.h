#pragma once
#include "MasterUI.h"



// Ό³Έν :
class Notches : public MasterUI
{
public:
	// constrcuter destructer
	Notches();
	~Notches();

	// delete Function
	Notches(const Notches& _Other) = delete;
	Notches(Notches&& _Other) noexcept = delete;
	Notches& operator=(const Notches& _Other) = delete;
	Notches& operator=(Notches&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isNotchesUsed_;

private:
	void SetNotchesUsed(bool _b)
	{
		GetRenderer()->SetTexture("charm_UI__0000_charm_cost_02_lit.png");
	}
};

