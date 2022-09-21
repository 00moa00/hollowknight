#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmFire : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmFire();
	~GrimmFire();

	// delete Function
	GrimmFire(const GrimmFire& _Other) = delete;
	GrimmFire(GrimmFire&& _Other) noexcept = delete;
	GrimmFire& operator=(const GrimmFire& _Other) = delete;
	GrimmFire& operator=(GrimmFire&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	//GameEngineTextureRenderer* MainRenderer_;

	float4 sprite_position;

	float RamdomRangeX_;
	float RamdomRangeY_;



public:
	//void CreateGrimmFireparticle(float4 ramX, float4 ramY);
};

 