#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GrimmFire.h"

// Ό³Έν :
class GrimmfireParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmfireParticle();
	~GrimmfireParticle();

	// delete Function
	GrimmfireParticle(const GrimmfireParticle& _Other) = delete;
	GrimmfireParticle(GrimmfireParticle&& _Other) noexcept = delete;
	GrimmfireParticle& operator=(const GrimmfireParticle& _Other) = delete;
	GrimmfireParticle& operator=(GrimmfireParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

