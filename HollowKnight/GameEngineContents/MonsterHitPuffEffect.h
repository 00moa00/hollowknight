#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class MonsterHitPuffEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterHitPuffEffect();
	~MonsterHitPuffEffect();

	// delete Function
	MonsterHitPuffEffect(const MonsterHitPuffEffect& _Other) = delete;
	MonsterHitPuffEffect(MonsterHitPuffEffect&& _Other) noexcept = delete;
	MonsterHitPuffEffect& operator=(const MonsterHitPuffEffect& _Other) = delete;
	MonsterHitPuffEffect& operator=(MonsterHitPuffEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Speed_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> DirList_;
	std::vector<float4> InitDir_;
	//std::vector<float4> InitScale_;
	//std::vector<bool> isEndMove_;

	std::vector<float4> StartDirList_;

public:
	void SetDir(float4 _Dir);

public:
};

 