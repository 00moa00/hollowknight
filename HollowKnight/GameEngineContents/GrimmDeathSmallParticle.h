#pragma once
#include <GameEngineCore/CoreMinimal.h>
// Ό³Έν :
class GrimmDeathSmallParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmDeathSmallParticle();
	~GrimmDeathSmallParticle();

	// delete Function
	GrimmDeathSmallParticle(const GrimmDeathSmallParticle& _Other) = delete;
	GrimmDeathSmallParticle(GrimmDeathSmallParticle&& _Other) noexcept = delete;
	GrimmDeathSmallParticle& operator=(const GrimmDeathSmallParticle& _Other) = delete;
	GrimmDeathSmallParticle& operator=(GrimmDeathSmallParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Scale_;
	float Length_;
	float Alpha_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> Dir_;
	std::vector<float4> InitScale_;

public:
	void ParticleOn();
};

