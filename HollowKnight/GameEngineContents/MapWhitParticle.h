#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MapWhitParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	MapWhitParticle();
	~MapWhitParticle();

	// delete Function
	MapWhitParticle(const MapWhitParticle& _Other) = delete;
	MapWhitParticle(MapWhitParticle&& _Other) noexcept = delete;
	MapWhitParticle& operator=(const MapWhitParticle& _Other) = delete;
	MapWhitParticle& operator=(MapWhitParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float AliveTimer_;
	float Alpha_;
	float Scale_;
	float Speed_;

	float4 Dir_;

	GameEngineTextureRenderer* ParticleRenderer_;

};

