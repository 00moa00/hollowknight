#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmBeam : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmBeam();
	~GrimmBeam();

	// delete Function
	GrimmBeam(const GrimmBeam& _Other) = delete;
	GrimmBeam(GrimmBeam&& _Other) noexcept = delete;
	GrimmBeam& operator=(const GrimmBeam& _Other) = delete;
	GrimmBeam& operator=(GrimmBeam&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

