#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class FadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeIn();
	~FadeIn();

	// delete Function
	FadeIn(const FadeIn& _Other) = delete;
	FadeIn(FadeIn&& _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn& _Other) = delete;
	FadeIn& operator=(FadeIn&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* Renderer_;
	float Alpha_;

	bool DeathFlag_;


public:
	bool GetDeathflag()
	{
		return DeathFlag_;
	}
};

