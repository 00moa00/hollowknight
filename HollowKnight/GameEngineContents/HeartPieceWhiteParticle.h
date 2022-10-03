#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class HeartPieceWhiteParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	HeartPieceWhiteParticle();
	~HeartPieceWhiteParticle();

	// delete Function
	HeartPieceWhiteParticle(const HeartPieceWhiteParticle& _Other) = delete;
	HeartPieceWhiteParticle(HeartPieceWhiteParticle&& _Other) noexcept = delete;
	HeartPieceWhiteParticle& operator=(const HeartPieceWhiteParticle& _Other) = delete;
	HeartPieceWhiteParticle& operator=(HeartPieceWhiteParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//float4 InitScale_;
	float Scale_;
	float Length_;
	float Alpha_;

	std::vector<GameEngineUIRenderer*> ParticleList_;
	std::vector<float4> Dir_;
	std::vector<float4> InitScale_;
	std::vector<float4> RamSpeed_;

public:
	void ParticleOn();
};

