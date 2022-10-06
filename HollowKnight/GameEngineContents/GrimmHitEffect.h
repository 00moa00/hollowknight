#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmHitEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmHitEffect();
	~GrimmHitEffect();

	// delete Function
	GrimmHitEffect(const GrimmHitEffect& _Other) = delete;
	GrimmHitEffect(GrimmHitEffect&& _Other) noexcept = delete;
	GrimmHitEffect& operator=(const GrimmHitEffect& _Other) = delete;
	GrimmHitEffect& operator=(GrimmHitEffect&& _Other) noexcept = delete;

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

public:
	void SetDir(float4 _Dir);
	void SetTexWhite();
	void SetisImpact(bool _b);

};

