#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

struct NoiseData
{
	float Time;
	float Dummy0;
	float Dummy1;
	float Dummy2;
};

class HollowKnightLevel;
class NoisePostEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	NoisePostEffect();
	~NoisePostEffect();

	// delete Function
	NoisePostEffect(const NoisePostEffect& _Other) = delete;
	NoisePostEffect(NoisePostEffect&& _Other) noexcept = delete;
	NoisePostEffect& operator=(const NoisePostEffect& _Other) = delete;
	NoisePostEffect& operator=(NoisePostEffect&& _Other) noexcept = delete;

public:
	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);

protected:
	GameEngineRenderTarget* CopyTarget;
	GameEngineRenderSet EffectSet;

	HollowKnightLevel* HollowKnightLevel_;

private:
	NoiseData NoiseData_;

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

