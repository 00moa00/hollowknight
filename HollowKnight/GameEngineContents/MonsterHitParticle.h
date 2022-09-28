#pragma once
#include <GameEngineCore/CoreMinimal.h>


// 각 랜더러는 애니메이션이 있다.
// 바닥에 닿으면 애니메이션 재생하고 죽는당
// 임팩트 온 -> 땅에 닿았았을 때 터진다. 
// 임펙트 오프 -> 땅에 닿았을때 터지지 않고(픽셀충돌을 하지 않고), 스케일이 작아진다. 
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
	bool isImpact_;

	float Scale_;
	float Speed_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> DirList_;
	std::vector<float4> InitDir_;
	std::vector<float4> InitScale_;
	std::vector<bool> isEndMove_;

	std::vector<float4> StartDirList_;

private:
	void isPixelCheck(float _DeltaTime);

public:
	void SetDir(float4 _Dir);
	void SetTexWhite();
	void SetisImpact(bool _b);
};

