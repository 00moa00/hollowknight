#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnightSlashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightSlashEffect();
	~KnightSlashEffect();

	// delete Function
	KnightSlashEffect(const KnightSlashEffect& _Other) = delete;
	KnightSlashEffect(KnightSlashEffect&& _Other) noexcept = delete;
	KnightSlashEffect& operator=(const KnightSlashEffect& _Other) = delete;
	KnightSlashEffect& operator=(KnightSlashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	GameEngineStateManager KnightSlashEffectManager_;
private:


	GameEngineRenderer* GameEngineRenderer_;

	//================================
	//    Bind State
	//================================

	//================================
	//    Bind Animation
	//================================
	void AnimationEndSlash(const FrameAnimation_DESC& _Info);
	void AnimationEndDoubleSlash(const FrameAnimation_DESC& _Info);
	void AnimationEndUpSlash(const FrameAnimation_DESC& _Info);
	void AnimationEndDownSlash(const FrameAnimation_DESC& _Info);

public:
	void SetAnimationSlash();
	void SetAnimationDoubleSlash();
	void SetAnimationUpSlash();
	void SetAnimationDownSlash();
	void SetAnimationStill();

	bool thisVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);

};

