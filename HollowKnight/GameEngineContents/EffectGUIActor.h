#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "EffectGUI.h"

// Ό³Έν :
class EffectGUIActor : public GameEngineActor
{
public:
	// constrcuter destructer
	EffectGUIActor();
	~EffectGUIActor();

	// delete Function
	EffectGUIActor(const EffectGUIActor& _Other) = delete;
	EffectGUIActor(EffectGUIActor&& _Other) noexcept = delete;
	EffectGUIActor& operator=(const EffectGUIActor& _Other) = delete;
	EffectGUIActor& operator=(EffectGUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;
	

private:
	EffectGUI* EffectGUI_;

public:
	bool GetisMainLightOnOff() const
	{
		return EffectGUI_->GetisMainLightOnOff();
	}

	bool GetisSiblingLightOnOff() const
	{
		return EffectGUI_->GetisSiblingLightOnOff();
	}

	bool GetisDonutLightOnOff() const
	{
		return EffectGUI_->GetisDonutLightOnOff();
	}



	float4 GetOverlayColor()
	{
		return EffectGUI_->GetColor();
	}

	bool GetOverlayFlag()
	{
		return EffectGUI_->GetOverlayFlag();
	}

	float4 GetMainLightMulColor()
	{
		return EffectGUI_->GetMainLightMulColor();

	}

	float4 GetMainLightPlusColor()
	{
		return EffectGUI_->GetMainLightPlusColor();

	}

	float4 GetSlibingLightMulColor()
	{
		return EffectGUI_->GetSlibingLightMulColor();

	}

	float4 GetSlibingLightPlusColor()
	{
		return EffectGUI_->GetSlibingLightPlusColor();

	}

	float4 GetDounutLightMulColor()
	{
		return EffectGUI_->GetDounutLightMulColor();

	}

	float4 GetDounutLightPlusColor()
	{
		return EffectGUI_->GetDounutLightPlusColor();

	}
};

