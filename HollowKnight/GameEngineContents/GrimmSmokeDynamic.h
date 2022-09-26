#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmSmokeDynamic : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmSmokeDynamic();
	~GrimmSmokeDynamic();

	// delete Function
	GrimmSmokeDynamic(const GrimmSmokeDynamic& _Other) = delete;
	GrimmSmokeDynamic(GrimmSmokeDynamic&& _Other) noexcept = delete;
	GrimmSmokeDynamic& operator=(const GrimmSmokeDynamic& _Other) = delete;
	GrimmSmokeDynamic& operator=(GrimmSmokeDynamic&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MoveDir_;
	float Alpha_;


public:
	void SetMoveDir(float4 _Dir);
};

 