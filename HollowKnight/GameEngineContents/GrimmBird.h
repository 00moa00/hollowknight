#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class GrimmBird : public MasterEffect
{
public:
	// constrcuter destructer
	GrimmBird();
	~GrimmBird();

	// delete Function
	GrimmBird(const GrimmBird& _Other) = delete;
	GrimmBird(GrimmBird&& _Other) noexcept = delete;
	GrimmBird& operator=(const GrimmBird& _Other) = delete;
	GrimmBird& operator=(GrimmBird&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MoveDir_;
	float Speed_;

public :
	void SetMoveDir(float4 _Dir);
};

