#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class GrimmFireBallSpectrumActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmFireBallSpectrumActor();
	~GrimmFireBallSpectrumActor();

	// delete Function
	GrimmFireBallSpectrumActor(const GrimmFireBallSpectrumActor& _Other) = delete;
	GrimmFireBallSpectrumActor(GrimmFireBallSpectrumActor&& _Other) noexcept = delete;
	GrimmFireBallSpectrumActor& operator=(const GrimmFireBallSpectrumActor& _Other) = delete;
	GrimmFireBallSpectrumActor& operator=(GrimmFireBallSpectrumActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float CreateTimer_;
	float UpdateTimer_;

};

