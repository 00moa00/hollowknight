#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"
#include "Elderbug.h"
#include "RoomPotal.h"

// Ό³Έν :
class DirtmouthLevel2 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	DirtmouthLevel2();
	~DirtmouthLevel2();

	// delete Function
	DirtmouthLevel2(const DirtmouthLevel2& _Other) = delete;
	DirtmouthLevel2(DirtmouthLevel2&& _Other) noexcept = delete;
	DirtmouthLevel2& operator=(const DirtmouthLevel2& _Other) = delete;
	DirtmouthLevel2& operator=(DirtmouthLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	Elderbug* Elderbug_;
	RoomPotal* MapShopPotal_;
	RoomPotal* SlyShopPotal_;

	GameEnginePostEffect* GameEnginePostEffect_;
};

