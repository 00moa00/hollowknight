#pragma once
#include <GameEngineCore/CoreMinimal.h>

// Ό³Έν :
class GrimmCrowd : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmCrowd();
	~GrimmCrowd();

	// delete Function
	GrimmCrowd(const GrimmCrowd& _Other) = delete;
	GrimmCrowd(GrimmCrowd&& _Other) noexcept = delete;
	GrimmCrowd& operator=(const GrimmCrowd& _Other) = delete;
	GrimmCrowd& operator=(GrimmCrowd&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* CrowdRenderer;

public:
	void SetScaleNegativeX();
};

