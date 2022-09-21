#pragma once
#include "MasterEffect.h"
#include <GameEngineBase/GameEngineRandom.h>

// Ό³Έν :
class GrimmFireBallSpectrum : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmFireBallSpectrum();
	~GrimmFireBallSpectrum();

	// delete Function
	GrimmFireBallSpectrum(const GrimmFireBallSpectrum& _Other) = delete;
	GrimmFireBallSpectrum(GrimmFireBallSpectrum&& _Other) noexcept = delete;
	GrimmFireBallSpectrum& operator=(const GrimmFireBallSpectrum& _Other) = delete;
	GrimmFireBallSpectrum& operator=(GrimmFireBallSpectrum&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Alpha_;
	float UpdateTimer_;
};

