#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>
// Ό³Έν :
class OverlayEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	OverlayEffect();
	~OverlayEffect();

	// delete Function
	OverlayEffect(const OverlayEffect& _Other) = delete;
	OverlayEffect(OverlayEffect&& _Other) noexcept = delete;
	OverlayEffect& operator=(const OverlayEffect& _Other) = delete;
	OverlayEffect& operator=(OverlayEffect&& _Other) noexcept = delete;

public:
	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;
};

