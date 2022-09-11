#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class KingsPassLevel1 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassLevel1();
	~KingsPassLevel1();

	// delete Function
	KingsPassLevel1(const KingsPassLevel1& _Other) = delete;
	KingsPassLevel1(KingsPassLevel1&& _Other) noexcept = delete;
	KingsPassLevel1& operator=(const KingsPassLevel1& _Other) = delete;
	KingsPassLevel1& operator=(KingsPassLevel1&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:


};

