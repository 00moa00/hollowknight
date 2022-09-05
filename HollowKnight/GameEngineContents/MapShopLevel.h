#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class MapShopLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	MapShopLevel();
	~MapShopLevel();

	// delete Function
	MapShopLevel(const MapShopLevel& _Other) = delete;
	MapShopLevel(MapShopLevel&& _Other) noexcept = delete;
	MapShopLevel& operator=(const MapShopLevel& _Other) = delete;
	MapShopLevel& operator=(MapShopLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
private:

};

