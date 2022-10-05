#pragma once
#include <GameEngineCore/CoreMinimal.h>


// Ό³Έν :
class LargeStoneParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	LargeStoneParticle();
	~LargeStoneParticle();

	// delete Function
	LargeStoneParticle(const LargeStoneParticle& _Other) = delete;
	LargeStoneParticle(LargeStoneParticle&& _Other) noexcept = delete;
	LargeStoneParticle& operator=(const LargeStoneParticle& _Other) = delete;
	LargeStoneParticle& operator=(LargeStoneParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Speed_;

	std::vector<float4> DirList_;
	std::vector<float4> InitDir_;

	std::vector<bool> isEndMove_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;


private:
	void isPixelDownCheck(float _DeltaTime);

public:
	void SetDir(float4 _Dir);
	void SetRamPos(float MinY, float MaxY);
};

