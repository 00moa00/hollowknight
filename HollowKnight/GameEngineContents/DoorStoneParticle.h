#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class DoorStoneParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	DoorStoneParticle();
	~DoorStoneParticle();

	// delete Function
	DoorStoneParticle(const DoorStoneParticle& _Other) = delete;
	DoorStoneParticle(DoorStoneParticle&& _Other) noexcept = delete;
	DoorStoneParticle& operator=(const DoorStoneParticle& _Other) = delete;
	DoorStoneParticle& operator=(DoorStoneParticle&& _Other) noexcept = delete;

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

};

