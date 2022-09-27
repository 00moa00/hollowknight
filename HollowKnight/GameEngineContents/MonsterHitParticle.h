#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineBase/GameEngineRandom.h>

// 각 랜더러는 애니메이션이 있다.
// 바닥에 닿으면 애니메이션 재생하고 죽는당
// 설명 :
class MonsterHitParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterHitParticle();
	~MonsterHitParticle();

	// delete Function
	MonsterHitParticle(const MonsterHitParticle& _Other) = delete;
	MonsterHitParticle(MonsterHitParticle&& _Other) noexcept = delete;
	MonsterHitParticle& operator=(const MonsterHitParticle& _Other) = delete;
	MonsterHitParticle& operator=(MonsterHitParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Scale_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> DirList_;
	std::vector<float4> InitDir_;

	std::vector<float4> StartDirList_;

private:
	void isPixelCheck(float _DeltaTime);

public:
	void SetDir(float4 _Dir);
};

