#pragma once

// Ό³Έν :
class TitleCircleParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleCircleParticle();
	~TitleCircleParticle();

	// delete Function
	TitleCircleParticle(const TitleCircleParticle& _Other) = delete;
	TitleCircleParticle(TitleCircleParticle&& _Other) noexcept = delete;
	TitleCircleParticle& operator=(const TitleCircleParticle& _Other) = delete;
	TitleCircleParticle& operator=(TitleCircleParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;


private:
	float AliveTimer_;
	float Scale_;
	float Speed_;

	GameEngineTextureRenderer* ParticleRenderer_;
};

