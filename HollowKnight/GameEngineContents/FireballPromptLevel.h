#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

#include "ContentsFontRenderer.h"

// Ό³Έν :
class FireballPromptLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	FireballPromptLevel();
	~FireballPromptLevel();

	// delete Function
	FireballPromptLevel(const FireballPromptLevel& _Other) = delete;
	FireballPromptLevel(FireballPromptLevel&& _Other) noexcept = delete;
	FireballPromptLevel& operator=(const FireballPromptLevel& _Other) = delete;
	FireballPromptLevel& operator=(FireballPromptLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:


};

