#pragma once
#include "MasterEffect.h"
#include "GrimmFireBallSpectrumActor.h"

enum class MoveType
{
	RightDown,
	RightUp,
	Right,

	LeftDown,
	LeftUp,
	Left,

	DownRight,
	DownLeft,
	Down
};

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
	float4 StartMoveDir_;

	float CreateTimer_;
	float Speed_;
	float CurvPower_;

	int Count_;

	MoveType MoveType_;

	std::vector<GrimmFireBallSpectrumActor*> AllSpecturumActor_;

public:
	void SetMoveDir(float4 _Dir, MoveType _Type);
	//void SetStartMoveDir(float4 _Dir);
};

 