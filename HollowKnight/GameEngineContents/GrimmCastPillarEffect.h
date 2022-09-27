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
	std::vector<float4> InitPos_;

	float a;
	float r;

	GameEngineStateManager CastPillarManager_;
public:
	void CastPillarEffectOn();
	void CaetPillarEffectOff();

private:
	void CastPillarFireStart(const StateInfo& _Info);
	void CastPillarFireUpdate(float _DeltaTime, const StateInfo& _Info);
	void CastPillarFireEnd(const StateInfo& _Info);

	void CastPillarDisappearStart(const StateInfo& _Info);
	void CastPillarDisappearUpdate(float _DeltaTime, const StateInfo& _Info);
	void CastPillarDisappearEnd(const StateInfo& _Info);

};

