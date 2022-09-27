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
	float4 MovePos_;
	float4 StartMoveDir_;

	float CreateTimer_;
	float Speed_;
	float CurvPower_;
	float SubScale_;

	int Count_;

	MoveType MoveType_;

	GameEngineStateManager GrimmFireStateManager;

	GameEngineTextureRenderer* FireBallRenderer1;
	GameEngineTextureRenderer* FireBallRenderer2;
	GameEngineTextureRenderer* FireBallRenderer3;

public:
	void SetMoveDir(float4 _Dir, MoveType _Type);

private:
	void FireMoveStart(const StateInfo& _Info);
	void FireMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void FireMoveEnd(const StateInfo& _Info);

	void FireDeathStart(const StateInfo& _Info);
	void FireDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void FireDeathEnd(const StateInfo& _Info);

};

 