#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class KnightDoubleJumpParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	KnightDoubleJumpParticle();
	~KnightDoubleJumpParticle();

	// delete Function
	KnightDoubleJumpParticle(const KnightDoubleJumpParticle& _Other) = delete;
	KnightDoubleJumpParticle(KnightDoubleJumpParticle&& _Other) noexcept = delete;
	KnightDoubleJumpParticle& operator=(const KnightDoubleJumpParticle& _Other) = delete;
	KnightDoubleJumpParticle& operator=(KnightDoubleJumpParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Scale_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> InitScale_;
	std::vector<float4> InitPos_;
	std::vector<float4> ScaleSpeed_;

	std::vector<float> RotationSpeed_;


public:
	void ParticleOn();
};

