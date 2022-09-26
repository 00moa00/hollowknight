#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmFlamePillarEffect : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmFlamePillarEffect();
	~GrimmFlamePillarEffect();

	// delete Function
	GrimmFlamePillarEffect(const GrimmFlamePillarEffect& _Other) = delete;
	GrimmFlamePillarEffect(GrimmFlamePillarEffect&& _Other) noexcept = delete;
	GrimmFlamePillarEffect& operator=(const GrimmFlamePillarEffect& _Other) = delete;
	GrimmFlamePillarEffect& operator=(GrimmFlamePillarEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

