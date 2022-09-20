#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class BossRoarEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BossRoarEffect();
	~BossRoarEffect();

	// delete Function
	BossRoarEffect(const BossRoarEffect& _Other) = delete;
	BossRoarEffect(BossRoarEffect&& _Other) noexcept = delete;
	BossRoarEffect& operator=(const BossRoarEffect& _Other) = delete;
	BossRoarEffect& operator=(BossRoarEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	float CreateTimer_;

	float Alpha_;
	float4 AddScale_;

	GameEngineTextureRenderer* RoarLineRenderer;

	//GameEngineTextureRenderer* RoarLineRenderer;

};

