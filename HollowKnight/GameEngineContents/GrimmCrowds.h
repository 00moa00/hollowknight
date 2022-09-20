#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "GrimmCrowd.h"

// Ό³Έν :
class GrimmCrowds : public GameEngineActor
{
public:
	// constrcuter destructer
	GrimmCrowds();
	~GrimmCrowds();

	// delete Function
	GrimmCrowds(const GrimmCrowds& _Other) = delete;
	GrimmCrowds(GrimmCrowds&& _Other) noexcept = delete;
	GrimmCrowds& operator=(const GrimmCrowds& _Other) = delete;
	GrimmCrowds& operator=(GrimmCrowds&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

