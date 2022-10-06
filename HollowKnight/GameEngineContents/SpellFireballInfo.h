#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include "ContentsFontRenderer.h"

#include "FadeOut.h"
// Ό³Έν :
class SpellFireballInfo : public GameEngineActor
{
public:
	// constrcuter destructer
	SpellFireballInfo();
	~SpellFireballInfo();

	// delete Function
	SpellFireballInfo(const SpellFireballInfo& _Other) = delete;
	SpellFireballInfo(SpellFireballInfo&& _Other) noexcept = delete;
	SpellFireballInfo& operator=(const SpellFireballInfo& _Other) = delete;
	SpellFireballInfo& operator=(SpellFireballInfo&& _Other) noexcept = delete;


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

