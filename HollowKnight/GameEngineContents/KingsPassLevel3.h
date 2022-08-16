#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

// Ό³Έν :
class KingsPassLevel3 : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassLevel3();
	~KingsPassLevel3();

	// delete Function
	KingsPassLevel3(const KingsPassLevel3& _Other) = delete;
	KingsPassLevel3(KingsPassLevel3&& _Other) noexcept = delete;
	KingsPassLevel3& operator=(const KingsPassLevel3& _Other) = delete;
	KingsPassLevel3& operator=(KingsPassLevel3&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

