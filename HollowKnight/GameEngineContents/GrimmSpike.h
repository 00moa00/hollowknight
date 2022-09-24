#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmSpike : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmSpike();
	~GrimmSpike();

	// delete Function
	GrimmSpike(const GrimmSpike& _Other) = delete;
	GrimmSpike(GrimmSpike&& _Other) noexcept = delete;
	GrimmSpike& operator=(const GrimmSpike& _Other) = delete;
	GrimmSpike& operator=(GrimmSpike&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Speed_;

	float CollMove_;

	GameEngineStateManager GrimmBirdStateManager;

private:
	void SpikeWaitStart(const StateInfo& _Info);
	void SpikeWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpikeWaitEnd(const StateInfo& _Info);

	void SpikeMoveUpStart(const StateInfo& _Info);
	void SpikeMoveUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpikeMoveUpEnd(const StateInfo& _Info);

	void SpikeMoveUpWaitStart(const StateInfo& _Info);
	void SpikeMoveUpWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpikeMoveUpWaitEnd(const StateInfo& _Info);

	void SpikeMoveDownStart(const StateInfo& _Info);
	void SpikeMoveDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void SpikeMoveDownEnd(const StateInfo& _Info);

};

