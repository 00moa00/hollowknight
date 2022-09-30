#pragma once

// Ό³Έν :
class TitleSmokeParticle
{
public:
	// constrcuter destructer
	TitleSmokeParticle();
	~TitleSmokeParticle();

	// delete Function
	TitleSmokeParticle(const TitleSmokeParticle& _Other) = delete;
	TitleSmokeParticle(TitleSmokeParticle&& _Other) noexcept = delete;
	TitleSmokeParticle& operator=(const TitleSmokeParticle& _Other) = delete;
	TitleSmokeParticle& operator=(TitleSmokeParticle&& _Other) noexcept = delete;

protected:

private:

};

