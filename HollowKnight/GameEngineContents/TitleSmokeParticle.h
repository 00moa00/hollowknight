#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class TitleSmokeParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleSmokeParticle();
	~TitleSmokeParticle();

	// delete Function
	TitleSmokeParticle(const TitleSmokeParticle& _Other) = delete;
	TitleSmokeParticle(TitleSmokeParticle&& _Other) noexcept = delete;
	TitleSmokeParticle& operator=(const TitleSmokeParticle& _Other) = delete;
	TitleSmokeParticle& operator=(TitleSmokeParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float AliveTimer_;
	float Alpha_;
	float Speed_;

	GameEngineTextureRenderer* ParticleRenderer_;

};

