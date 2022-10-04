#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class KnightRoarEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	KnightRoarEffect();
	~KnightRoarEffect();

	// delete Function
	KnightRoarEffect(const KnightRoarEffect& _Other) = delete;
	KnightRoarEffect(KnightRoarEffect&& _Other) noexcept = delete;
	KnightRoarEffect& operator=(const KnightRoarEffect& _Other) = delete;
	KnightRoarEffect& operator=(KnightRoarEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float CreateTimer_;

	float Alpha_;
	float4 AddScale_;

	GameEngineTextureRenderer* RoarLineRenderer;

};

