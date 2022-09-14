#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class DirtmouthStationLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	DirtmouthStationLevel();
	~DirtmouthStationLevel();

	// delete Function
	DirtmouthStationLevel(const DirtmouthStationLevel& _Other) = delete;
	DirtmouthStationLevel(DirtmouthStationLevel&& _Other) noexcept = delete;
	DirtmouthStationLevel& operator=(const DirtmouthStationLevel& _Other) = delete;
	DirtmouthStationLevel& operator=(DirtmouthStationLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;


private:

};

