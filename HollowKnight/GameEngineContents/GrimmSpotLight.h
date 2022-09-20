#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmSpotLight : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmSpotLight();
	~GrimmSpotLight();

	// delete Function
	GrimmSpotLight(const GrimmSpotLight& _Other) = delete;
	GrimmSpotLight(GrimmSpotLight&& _Other) noexcept = delete;
	GrimmSpotLight& operator=(const GrimmSpotLight& _Other) = delete;
	GrimmSpotLight& operator=(GrimmSpotLight&& _Other) noexcept = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

