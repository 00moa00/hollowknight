#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class SlyShopLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	SlyShopLevel();
	~SlyShopLevel();

	// delete Function
	SlyShopLevel(const SlyShopLevel& _Other) = delete;
	SlyShopLevel(SlyShopLevel&& _Other) noexcept = delete;
	SlyShopLevel& operator=(const SlyShopLevel& _Other) = delete;
	SlyShopLevel& operator=(SlyShopLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

