#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct OverlayColorData
{
	float4 OverlayColor = { 0.499f, 0.592f, 0.726f, 1.0f };
	int isOverlay_ = true;

};

class HollowKnightLevel;
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

private:
	GameEngineRenderSet EffectSet;
	OverlayColorData OverlayColorData_;

	GameEngineRenderTarget* CopyTarget;
	GameEngineTexture* Overlay_;
	HollowKnightLevel* HollowKnightLevel_;

public:
	HollowKnightLevel* GetHollowKnightLevel()
	{
		return HollowKnightLevel_;
	}

	 void SetHollowKnightLevel(HollowKnightLevel* _level)
	 {
		 HollowKnightLevel_ = _level;
	 }

};

