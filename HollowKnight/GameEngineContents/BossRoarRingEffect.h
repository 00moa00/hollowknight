#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class BossRoarRingEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BossRoarRingEffect();
	~BossRoarRingEffect();

	// delete Function
	BossRoarRingEffect(const BossRoarRingEffect& _Other) = delete;
	BossRoarRingEffect(BossRoarRingEffect&& _Other) noexcept = delete;
	BossRoarRingEffect& operator=(const BossRoarRingEffect& _Other) = delete;
	BossRoarRingEffect& operator=(BossRoarRingEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Alpha_;

	float4 AddScale_;

	GameEngineTextureRenderer* RoarRingRenderer_;

};

