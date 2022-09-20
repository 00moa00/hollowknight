#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class FadePink : public GameEngineActor
{
public:
	// constrcuter destructer
	FadePink();
	~FadePink();

	// delete Function
	FadePink(const FadePink& _Other) = delete;
	FadePink(FadePink&& _Other) noexcept = delete;
	FadePink& operator=(const FadePink& _Other) = delete;
	FadePink& operator=(FadePink&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* PinkRenderer_;
	float Alpha_;

};

