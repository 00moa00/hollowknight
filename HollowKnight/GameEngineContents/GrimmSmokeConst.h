#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmSmokeConst : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmSmokeConst();
	~GrimmSmokeConst();

	// delete Function
	GrimmSmokeConst(const GrimmSmokeConst& _Other) = delete;
	GrimmSmokeConst(GrimmSmokeConst&& _Other) noexcept = delete;
	GrimmSmokeConst& operator=(const GrimmSmokeConst& _Other) = delete;
	GrimmSmokeConst& operator=(GrimmSmokeConst&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

