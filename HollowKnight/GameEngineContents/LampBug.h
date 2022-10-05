#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class LampBug : public MasterEffect
{
public:
	// constrcuter destructer
	LampBug();
	~LampBug();

	// delete Function
	LampBug(const LampBug& _Other) = delete;
	LampBug(LampBug&& _Other) noexcept = delete;
	LampBug& operator=(const LampBug& _Other) = delete;
	LampBug& operator=(LampBug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 Dir_;
	float4 LimitMoveSize_;
	float4 PivotPos_;

	float Alpha_;

	float AlphaTImer_;

	GameEngineStateManager BugManager_;


public:
	void SetLimitMove(float4 _CurrentPos, float4 _LimitSize);

	void MovingBug();

private:
	//================================
	//    Bind State
	//================================

	void LmapBugIdleStart(const StateInfo& _Info);
	void LmapBugIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void LmapBugIdleEnd(const StateInfo& _Info);

	void LmapBugHideStart(const StateInfo& _Info);
	void LmapBugHideUpdate(float _DeltaTime, const StateInfo& _Info);
	void LmapBugHideEnd(const StateInfo& _Info);


};

