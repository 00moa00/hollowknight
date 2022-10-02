#pragma once

// Ό³Έν :
class KnightWalkDustParticle
{
public:
	// constrcuter destructer
	KnightWalkDustParticle();
	~KnightWalkDustParticle();

	// delete Function
	KnightWalkDustParticle(const KnightWalkDustParticle& _Other) = delete;
	KnightWalkDustParticle(KnightWalkDustParticle&& _Other) noexcept = delete;
	KnightWalkDustParticle& operator=(const KnightWalkDustParticle& _Other) = delete;
	KnightWalkDustParticle& operator=(KnightWalkDustParticle&& _Other) noexcept = delete;

protected:

private:

};

