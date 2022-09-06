#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>
// Ό³Έν :
class OverlayPostEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	OverlayPostEffect();
	~OverlayPostEffect();

	// delete Function
	OverlayPostEffect(const OverlayPostEffect& _Other) = delete;
	OverlayPostEffect(OverlayPostEffect&& _Other) noexcept = delete;
	OverlayPostEffect& operator=(const OverlayPostEffect& _Other) = delete;
	OverlayPostEffect& operator=(OverlayPostEffect&& _Other) noexcept = delete;

public:
	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

private:
	GameEngineTexture* Overlay_;
	 
};

