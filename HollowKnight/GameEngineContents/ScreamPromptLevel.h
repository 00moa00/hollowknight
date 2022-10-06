#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"

#include "ContentsFontRenderer.h"
// Ό³Έν :
class ScreamPromptLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	ScreamPromptLevel();
	~ScreamPromptLevel();

	// delete Function
	ScreamPromptLevel(const ScreamPromptLevel& _Other) = delete;
	ScreamPromptLevel(ScreamPromptLevel&& _Other) noexcept = delete;
	ScreamPromptLevel& operator=(const ScreamPromptLevel& _Other) = delete;
	ScreamPromptLevel& operator=(ScreamPromptLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

};

