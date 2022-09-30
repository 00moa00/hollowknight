#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "HollowKnightLevel.h"
#include "RendererActor.h"
#include "AllTitleUI.h"

// 설명 : 랜더러 액터 왜 만들었담...

class TitleLevel : public HollowKnightLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	RendererActor* Background_;
	RendererActor* LogoRenderer_;
	AllTitleUI* MasterTitleUI_;

	float CircleParticleCreateTimer_;
	float SmokeParticleCreateTimer_;
	float WhiteParticleCreateTimer_;
};

