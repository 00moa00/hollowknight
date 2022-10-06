#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class DirtmouthLevel1 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	DirtmouthLevel1();
	~DirtmouthLevel1();

	// delete Function
	DirtmouthLevel1(const DirtmouthLevel1& _Other) = delete;
	DirtmouthLevel1(DirtmouthLevel1&& _Other) noexcept = delete;
	DirtmouthLevel1& operator=(const DirtmouthLevel1& _Other) = delete;
	DirtmouthLevel1& operator=(DirtmouthLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	bool isFirst_;

};

