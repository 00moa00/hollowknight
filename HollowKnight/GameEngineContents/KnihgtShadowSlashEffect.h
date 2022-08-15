#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class KnihgtShadowSlashEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnihgtShadowSlashEffect();
	~KnihgtShadowSlashEffect();

	// delete Function
	KnihgtShadowSlashEffect(const KnihgtShadowSlashEffect& _Other) = delete;
	KnihgtShadowSlashEffect(KnihgtShadowSlashEffect&& _Other) noexcept = delete;
	KnihgtShadowSlashEffect& operator=(const KnihgtShadowSlashEffect& _Other) = delete;
	KnihgtShadowSlashEffect& operator=(KnihgtShadowSlashEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineStateManager ShadowSlashEffectManager_;

private:
	//================================
	//    Bind Animation
	//================================

	//bool EffectVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


};

