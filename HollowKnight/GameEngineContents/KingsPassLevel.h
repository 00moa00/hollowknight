#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"


// Ό³Έν :
class KingsPassLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassLevel();
	~KingsPassLevel();

	// delete Function
	KingsPassLevel(const KingsPassLevel& _Other) = delete;
	KingsPassLevel(KingsPassLevel&& _Other) noexcept = delete;
	KingsPassLevel& operator=(const KingsPassLevel& _Other) = delete;
	KingsPassLevel& operator=(KingsPassLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	MasterMap* MasterMap_;
	Knight* Knight_;
};

