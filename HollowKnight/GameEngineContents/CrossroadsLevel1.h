#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"
#include "SideDarkEffect.h"

// Ό³Έν :
class CrossroadsLevel1 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	CrossroadsLevel1();
	~CrossroadsLevel1();

	// delete Function
	CrossroadsLevel1(const CrossroadsLevel1& _Other) = delete;
	CrossroadsLevel1(CrossroadsLevel1&& _Other) noexcept = delete;
	CrossroadsLevel1& operator=(const CrossroadsLevel1& _Other) = delete;
	CrossroadsLevel1& operator=(CrossroadsLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;

private:

};

