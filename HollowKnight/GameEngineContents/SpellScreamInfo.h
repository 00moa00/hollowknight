#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "ContentsFontRenderer.h"

#include "FadeOut.h"

// Ό³Έν :
class SpellScreamInfo : public GameEngineActor
{
public:
	// constrcuter destructer
	SpellScreamInfo();
	~SpellScreamInfo();

	// delete Function
	SpellScreamInfo(const SpellScreamInfo& _Other) = delete;
	SpellScreamInfo(SpellScreamInfo&& _Other) noexcept = delete;
	SpellScreamInfo& operator=(const SpellScreamInfo& _Other) = delete;
	SpellScreamInfo& operator=(SpellScreamInfo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	GameEngineUIRenderer* BackTexture;

	GameEngineUIRenderer* SpellTexture;

	GameEngineUIRenderer* DividerTexture;

	FadeOut* FadeOut_;


	ContentsFontRenderer* SpellName_;
	ContentsFontRenderer* SpellInfo_;


	float SpellAlpha_;
	float DividerAlpha_;
	float NameAlpha_;
	float InfoAlpha_;
};

