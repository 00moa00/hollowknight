#pragma once
#include "MasterEffect.h"
#include "GrimmFireBallSpectrumActor.h"

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

	float4 MovePos_;

	float CreateTimer_;

	int Count_;

	std::vector<GrimmFireBallSpectrumActor*> AllSpecturumActor_;

public:
	void SetMoveDir(float4 _Dir);
};

 