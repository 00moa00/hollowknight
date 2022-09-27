#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmCastPillarEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmCastPillarEffect();
	~GrimmCastPillarEffect();

	// delete Function
	GrimmCastPillarEffect(const GrimmCastPillarEffect& _Other) = delete;
	GrimmCastPillarEffect(GrimmCastPillarEffect&& _Other) noexcept = delete;
	GrimmCastPillarEffect& operator=(const GrimmCastPillarEffect& _Other) = delete;
	GrimmCastPillarEffect& operator=(GrimmCastPillarEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> ScaleList_;
	float Alpha_;
public:
};

