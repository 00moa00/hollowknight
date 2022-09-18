#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsFontRenderer.h"

// Ό³Έν :
class SpellFocusInfo : public GameEngineActor
{
public:
	// constrcuter destructer
	SpellFocusInfo();
	~SpellFocusInfo();

	// delete Function
	SpellFocusInfo(const SpellFocusInfo& _Other) = delete;
	SpellFocusInfo(SpellFocusInfo&& _Other) noexcept = delete;
	SpellFocusInfo& operator=(const SpellFocusInfo& _Other) = delete;
	SpellFocusInfo& operator=(SpellFocusInfo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float Alpha_;

	GameEngineUIRenderer* SpellTexture;

	ContentsFontRenderer* FocusInfo1_;
	ContentsFontRenderer* FocusInfo2_;
	ContentsFontRenderer* FocusInfo3_;

	GameEngineStateManager SpellFocusInfoManager_;

public:
	void SetSpellFocusInfoOn();
	void SetSpellFocusInfoOff();


private:
	//================================
	//    Bind 
	//================================
	void SpellFocusInfoIdleStart(const StateInfo& _Info);
	void SpellFocusInfoIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpellFocusInfoIdleEnd(const StateInfo& _Info);

	void SpellFocusInfoOnDialougueStart(const StateInfo& _Info);
	void SpellFocusInfoOnDialougueUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpellFocusInfoOnDialougueEnd(const StateInfo& _Info);

	void SpellFocusInfoOffDialougueStart(const StateInfo& _Info);
	void SpellFocusInfoOffDialougueUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpellFocusInfoOffDialougueEnd(const StateInfo& _Info);

};

