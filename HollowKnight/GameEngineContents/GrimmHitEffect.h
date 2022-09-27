#pragma once

// Ό³Έν :
class GrimmHitEffect
{
public:
	// constrcuter destructer
	GrimmHitEffect();
	~GrimmHitEffect();

	// delete Function
	GrimmHitEffect(const GrimmHitEffect& _Other) = delete;
	GrimmHitEffect(GrimmHitEffect&& _Other) noexcept = delete;
	GrimmHitEffect& operator=(const GrimmHitEffect& _Other) = delete;
	GrimmHitEffect& operator=(GrimmHitEffect&& _Other) noexcept = delete;

protected:

private:

};

