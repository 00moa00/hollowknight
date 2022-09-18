#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>
// Ό³Έν :
class FadeOut : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeOut();
	~FadeOut();

	// delete Function
	FadeOut(const FadeOut& _Other) = delete;
	FadeOut(FadeOut&& _Other) noexcept = delete;
	FadeOut& operator=(const FadeOut& _Other) = delete;
	FadeOut& operator=(FadeOut&& _Other) noexcept = delete;

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

