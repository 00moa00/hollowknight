#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmBird : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmBird();
	~GrimmBird();

	// delete Function
	GrimmBird(const GrimmBird& _Other) = delete;
	GrimmBird(GrimmBird&& _Other) noexcept = delete;
	GrimmBird& operator=(const GrimmBird& _Other) = delete;
	GrimmBird& operator=(GrimmBird&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Speed_;
	float ParticleCreateTimer_;

	float4 MoveDir_;

	GameEngineTextureRenderer* BirdDeathEffect_;


	GameEngineStateManager GrimmBirdStateManager;

public :
	void SetMoveDir(float4 _Dir);

private:
	void BirdMoveStart(const StateInfo& _Info);
	void BirdMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void BirdMoveEnd(const StateInfo& _Info);


	void BirdDeathStart(const StateInfo& _Info);
	void BirdDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void BirdDeathEnd(const StateInfo& _Info);

};

