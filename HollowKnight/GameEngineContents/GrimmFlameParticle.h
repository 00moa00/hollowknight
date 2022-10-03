#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmFlameParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmFlameParticle();
	~GrimmFlameParticle();

	// delete Function
	GrimmFlameParticle(const GrimmFlameParticle& _Other) = delete;
	GrimmFlameParticle(GrimmFlameParticle&& _Other) noexcept = delete;
	GrimmFlameParticle& operator=(const GrimmFlameParticle& _Other) = delete;
	GrimmFlameParticle& operator=(GrimmFlameParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float a;
	float r;
	std::vector<GameEngineTextureRenderer*> ParticleList_;


};

