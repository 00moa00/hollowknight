#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class GrimmSmoke : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmSmoke();
	~GrimmSmoke();

	// delete Function
	GrimmSmoke(const GrimmSmoke& _Other) = delete;
	GrimmSmoke(GrimmSmoke&& _Other) noexcept = delete;
	GrimmSmoke& operator=(const GrimmSmoke& _Other) = delete;
	GrimmSmoke& operator=(GrimmSmoke&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 RightMoveDir_;
	float4 LeftMoveDir_;

	float Alpha_;

	std::vector<GameEngineTextureRenderer*> BottomSmoke_;
	std::vector<GameEngineTextureRenderer*> TopRightSmoke_;
	std::vector<GameEngineTextureRenderer*> TopLeftSmoke_;

	std::vector<float4> BottomInitPos_;
	std::vector<float4> TopRightInitPos_;
	std::vector<float4> TopLeftInitPos_;

public:
	void SetSmokeOn();
	void SetSmokeOff();


};

