#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

// Ό³Έν :
class VignettePostEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	VignettePostEffect();
	~VignettePostEffect();

	// delete Function
	VignettePostEffect(const VignettePostEffect& _Other) = delete;
	VignettePostEffect(VignettePostEffect&& _Other) noexcept = delete;
	VignettePostEffect& operator=(const VignettePostEffect& _Other) = delete;
	VignettePostEffect& operator=(VignettePostEffect&& _Other) noexcept = delete;
public:
	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

private:

};

