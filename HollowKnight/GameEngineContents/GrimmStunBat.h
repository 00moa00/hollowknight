#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmStunBat : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmStunBat();
	~GrimmStunBat();

	// delete Function
	GrimmStunBat(const GrimmStunBat& _Other) = delete;
	GrimmStunBat(GrimmStunBat&& _Other) noexcept = delete;
	GrimmStunBat& operator=(const GrimmStunBat& _Other) = delete;
	GrimmStunBat& operator=(GrimmStunBat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isMoveGrimm_;

	float Speed_;


	float4 MoveDir_;
	float4 TargetPos_;

	GameEngineStateManager GrimmBirdStateManager;

public:
	void SetMoveToGrimm(float4 _TargetPos);

	bool GetisMovetoGrimm() const
	{
		return isMoveGrimm_;
	}

private:
	void ChangeScaleX();

	void BatFlyStart(const StateInfo& _Info);
	void BatFlyUpdate(float _DeltaTime, const StateInfo& _Info);
	void BatFlyEnd(const StateInfo& _Info);

	void BatMoveToGrimmStart(const StateInfo& _Info);
	void BatMoveToGrimmUpdate(float _DeltaTime, const StateInfo& _Info);
	void BatMoveToGrimmEnd(const StateInfo& _Info);

	void BatDeathWaitStart(const StateInfo& _Info);
	void BatDeathWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void BatDeathWaitEnd(const StateInfo& _Info);

};

