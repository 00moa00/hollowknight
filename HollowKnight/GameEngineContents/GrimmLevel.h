#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

#include "Grimm.h"
#include "GrimmCrowds.h"
#include "OverlayPostEffect.h"

// Ό³Έν :
class GrimmLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	GrimmLevel();
	~GrimmLevel();

	// delete Function
	GrimmLevel(const GrimmLevel& _Other) = delete;
	GrimmLevel(GrimmLevel&& _Other) noexcept = delete;
	GrimmLevel& operator=(const GrimmLevel& _Other) = delete;
	GrimmLevel& operator=(GrimmLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime)override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	Grimm* Grimm_;
	GrimmCrowds* GrimmCrowds_;
	//OverlayPostEffect* EventOverlayPostEffect_;

public:
	GrimmCrowds* GetGrimmCrowds()
	{
		return GrimmCrowds_;
	}
};

