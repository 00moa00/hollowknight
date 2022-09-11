#pragma once
#include "MasterUI.h"


class MaskState
{
public:
	bool isBroken_;
	bool isRefill_;
	bool isAppear_;
	bool isNewAppear_;
	bool isIdle_;
};

// 설명 :
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
	MaskState MaskState_;

	float IdleAnimationTimer_;

	GameEngineStateManager MaskManager_;

	//================================
	//    애니메이션
	//================================

	bool isAppearEnd_;
	bool isBreakEnd_;
	bool isRefillEnd_;
	bool isNewAppearEnd_;
	bool isIdleAnimationEnd_;

public:

	bool GetisBroken()
	{
		return MaskState_.isBroken_;
	}

	bool GetisRefill()
	{
		return MaskState_.isRefill_;
	}

	bool GetisAppear()
	{
		return MaskState_.isAppear_;
	}

	bool GetisNewAppear()
	{
		return MaskState_.isNewAppear_;
	}

	bool GetisIdle()
	{
		return MaskState_.isIdle_;
	}

	void SetisBroken()
	{
		MaskState_.isBroken_ = true;
		MaskState_.isRefill_ = false;
		MaskState_.isAppear_ = false;
		MaskState_.isNewAppear_ = false;
		MaskState_.isIdle_ = false;

	}

	void SetisRefill()
	{
		MaskState_.isBroken_ = false;
		MaskState_.isRefill_ = true;
		MaskState_.isAppear_ = false;
		MaskState_.isNewAppear_ = false;
		MaskState_.isIdle_ = false;

	}

	void SetisAppear()
	{
		MaskState_.isBroken_ = false;
		MaskState_.isRefill_ = false;
		MaskState_.isAppear_ = true;
		MaskState_.isNewAppear_ = false;
		MaskState_.isIdle_ = false;

	}

	void SetisNewAppear()
	{
		MaskState_.isBroken_ = false;
		MaskState_.isRefill_ = false;
		MaskState_.isAppear_ = false;
		MaskState_.isNewAppear_ = true;
		MaskState_.isIdle_ = false;

	}

	void SetisIdle()
	{
		MaskState_.isBroken_ = false;
		MaskState_.isRefill_ = false;
		MaskState_.isAppear_ = false;
		MaskState_.isNewAppear_ = false;
		MaskState_.isIdle_ = true;
	}

public:

	void SetWaitState();
	void SetAppearState();
	void SetNewAppearState();

	void SetIdleState();

	void SetBrokenAnimation();


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

	void MaskBreakStart(const StateInfo& _Info);
	void MaskBreakUpdate(float _DeltaTime, const StateInfo& _Info);
	void MaskBreakEnd(const StateInfo& _Info);

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

