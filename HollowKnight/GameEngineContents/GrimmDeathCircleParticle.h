#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmDeathCircleParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmDeathCircleParticle();
	~GrimmDeathCircleParticle();

	// delete Function
	GrimmDeathCircleParticle(const GrimmDeathCircleParticle& _Other) = delete;
	GrimmDeathCircleParticle(GrimmDeathCircleParticle&& _Other) noexcept = delete;
	GrimmDeathCircleParticle& operator=(const GrimmDeathCircleParticle& _Other) = delete;
	GrimmDeathCircleParticle& operator=(GrimmDeathCircleParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 InitScale_;
	float Scale_;
	float Length_;
	float Alpha_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> Dir_;

public:
	void ParticleOn();

};

