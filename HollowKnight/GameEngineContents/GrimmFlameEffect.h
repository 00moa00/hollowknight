#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmFlameEffect : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmFlameEffect();
	~GrimmFlameEffect();

	// delete Function
	GrimmFlameEffect(const GrimmFlameEffect& _Other) = delete;
	GrimmFlameEffect(GrimmFlameEffect&& _Other) noexcept = delete;
	GrimmFlameEffect& operator=(const GrimmFlameEffect& _Other) = delete;
	GrimmFlameEffect& operator=(GrimmFlameEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* LightRenderer_;
};

