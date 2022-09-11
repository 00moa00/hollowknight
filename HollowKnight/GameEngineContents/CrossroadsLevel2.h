#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class CrossroadsLevel2 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	CrossroadsLevel2();
	~CrossroadsLevel2();

	// delete Function
	CrossroadsLevel2(const CrossroadsLevel2& _Other) = delete;
	CrossroadsLevel2(CrossroadsLevel2&& _Other) noexcept = delete;
	CrossroadsLevel2& operator=(const CrossroadsLevel2& _Other) = delete;
	CrossroadsLevel2& operator=(CrossroadsLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

