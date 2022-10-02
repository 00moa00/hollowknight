#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"


// Ό³Έν :
class KingsPassGrimmOpenLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	KingsPassGrimmOpenLevel();
	~KingsPassGrimmOpenLevel();

	// delete Function
	KingsPassGrimmOpenLevel(const KingsPassGrimmOpenLevel& _Other) = delete;
	KingsPassGrimmOpenLevel(KingsPassGrimmOpenLevel&& _Other) noexcept = delete;
	KingsPassGrimmOpenLevel& operator=(const KingsPassGrimmOpenLevel& _Other) = delete;
	KingsPassGrimmOpenLevel& operator=(KingsPassGrimmOpenLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

