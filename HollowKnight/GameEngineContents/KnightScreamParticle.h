#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class KnightScreamParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	KnightScreamParticle();
	~KnightScreamParticle();

	// delete Function
	KnightScreamParticle(const KnightScreamParticle& _Other) = delete;
	KnightScreamParticle(KnightScreamParticle&& _Other) noexcept = delete;
	KnightScreamParticle& operator=(const KnightScreamParticle& _Other) = delete;
	KnightScreamParticle& operator=(KnightScreamParticle&& _Other) noexcept = delete;

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
	std::vector<float4> InitPos_;
	std::vector<float4> RamSpeed_;
	std::vector<float> InitAlpha_;

public:
	void ParticleOn();
};

