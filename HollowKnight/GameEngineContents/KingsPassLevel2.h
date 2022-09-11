#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class KingsPassLevel2 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassLevel2();
	~KingsPassLevel2();

	// delete Function
	KingsPassLevel2(const KingsPassLevel2& _Other) = delete;
	KingsPassLevel2(KingsPassLevel2&& _Other) noexcept = delete;
	KingsPassLevel2& operator=(const KingsPassLevel2& _Other) = delete;
	KingsPassLevel2& operator=(KingsPassLevel2&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;
	void LevelEndEvent() override;

private:

};

