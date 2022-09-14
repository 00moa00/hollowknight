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
	float4 GetOverlayColor()
	{
		return EffectGUI_->GetColor();
	}

	bool GetOverlayFlag()
	{
		return EffectGUI_->GetOverlayFlag();
	}
};

