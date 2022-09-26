#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

// Ό³Έν :
class GrimmFlameBallparticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmFlameBallparticle();
	~GrimmFlameBallparticle();

	// delete Function
	GrimmFlameBallparticle(const GrimmFlameBallparticle& _Other) = delete;
	GrimmFlameBallparticle(GrimmFlameBallparticle&& _Other) noexcept = delete;
	GrimmFlameBallparticle& operator=(const GrimmFlameBallparticle& _Other) = delete;
	GrimmFlameBallparticle& operator=(GrimmFlameBallparticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 InitScale_;
	float Scale_;
	float Length_;
	float Alpha_;

	//float4 Dir_;

	std::vector<GameEngineTextureRenderer*> BallParticleList_;
	std::vector<float4> Dir_;
	std::vector<float4> ScaleList_;
	std::vector<float4> InitPos_;

public:
	void SetLength(float _f)
	{
		Length_ = _f;
	}

public :
	void FlameBallparticleOn();

};

