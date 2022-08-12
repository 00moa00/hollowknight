#pragma once
#include "MasterUI.h"

// Ό³Έν :
class Mask : public MasterUI
{
public:
	// constrcuter destructer
	Mask();
	~Mask();

	// delete Function
	Mask(const Mask& _Other) = delete;
	Mask(Mask&& _Other) noexcept = delete;
	Mask& operator=(const Mask& _Other) = delete;
	Mask& operator=(Mask&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool isAppearEnd_;
	bool isBreakEnd_;
	bool isRefillEnd_;
	bool isNewAppearEnd_;
	bool isIdleAnimationEnd_;


	float IdleAnimationTimer_;

	GameEngineStateManager MaskManager_;
public:

	void SetWaitState();
	void SetAppearState();

	void SetIdleState();


private:

	//================================
	//    Bind State
	//================================

	void MaskWaitStart(const StateInfo& _Info);
	void MaskWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskWaitEnd(const StateInfo& _Info);

	void MaskAppearStart(const StateInfo& _Info);
	void MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskAppearEnd(const StateInfo& _Info);

	void MaskIdleStart(const StateInfo& _Info);
	void MaskIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskIdleEnd(const StateInfo& _Info);

	void MaskBrokenStart(const StateInfo& _Info);
	void MaskBrokenUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskBrokenEnd(const StateInfo& _Info);

	void MaskRefillStart(const StateInfo& _Info);
	void MaskRefillUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskRefillEnd(const StateInfo& _Info);

	void MaskNewAppearStart(const StateInfo& _Info);
	void MaskNewAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskNewAppearEnd(const StateInfo& _Info);
};

