#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MonsterDeathPuffParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterDeathPuffParticle();
	~MonsterDeathPuffParticle();

	// delete Function
	MonsterDeathPuffParticle(const MonsterDeathPuffParticle& _Other) = delete;
	MonsterDeathPuffParticle(MonsterDeathPuffParticle&& _Other) noexcept = delete;
	MonsterDeathPuffParticle& operator=(const MonsterDeathPuffParticle& _Other) = delete;
	MonsterDeathPuffParticle& operator=(MonsterDeathPuffParticle&& _Other) noexcept = delete;

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
	//std::vector<float4> ScaleList_;
	//std::vector<float4> InitPos_;

public:
	void ParticleOn();
};

