#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmDeathExplosionParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmDeathExplosionParticle();
	~GrimmDeathExplosionParticle();

	// delete Function
	GrimmDeathExplosionParticle(const GrimmDeathExplosionParticle& _Other) = delete;
	GrimmDeathExplosionParticle(GrimmDeathExplosionParticle&& _Other) noexcept = delete;
	GrimmDeathExplosionParticle& operator=(const GrimmDeathExplosionParticle& _Other) = delete;
	GrimmDeathExplosionParticle& operator=(GrimmDeathExplosionParticle&& _Other) noexcept = delete;

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

