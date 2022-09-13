#pragma once
#include "MasterEffect.h"



// Ό³Έν :
class KnightStunEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightStunEffect();
	~KnightStunEffect();

	// delete Function
	KnightStunEffect(const KnightStunEffect& _Other) = delete;
	KnightStunEffect(KnightStunEffect&& _Other) noexcept = delete;
	KnightStunEffect& operator=(const KnightStunEffect& _Other) = delete;
	KnightStunEffect& operator=(KnightStunEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 PrevScale_;
	float AddScaleX_;


	//GameEngineTextureRenderer* BlackParticle1;


public:
	void StunEffectOn();
	void StunEffectOff();

};

