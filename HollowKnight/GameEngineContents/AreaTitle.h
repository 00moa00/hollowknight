#pragma once
#include "MasterUI.h"
#include "AreaTitleTop.h"
#include "AreaTitleBottom.h"

#include <GameEngineCore/GameEngineFontRenderer.h>


// Ό³Έν :
class AreaTitle : public MasterUI
{
public:
	// constrcuter destructer
	AreaTitle();
	~AreaTitle();

	// delete Function
	AreaTitle(const AreaTitle& _Other) = delete;
	AreaTitle(AreaTitle&& _Other) noexcept = delete;
	AreaTitle& operator=(const AreaTitle& _Other) = delete;
	AreaTitle& operator=(AreaTitle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float Alpha_;
	float AlphaTimer_;

	AreaTitleTop* AreaTitleTop_;
	AreaTitleBottom* AreaTitleBottom_;

	GameEngineFontRenderer* GameTitleFont_;
	GameEngineFontRenderer* GameTitleBottomFont_;

	GameEngineStateManager AreaTitleStateManager_;

	void AreaTitleAppearStart(const StateInfo& _Info);
	void AreaTitleAppearUpdate(float _DeltaTime, const StateInfo& _Info);
	void AreaTitleAppearEnd(const StateInfo& _Info);

	void AreaTitleIdleStart(const StateInfo& _Info);
	void AreaTitleIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void AreaTitleIdleEnd(const StateInfo& _Info);

	void AreaTitleByeStart(const StateInfo& _Info);
	void AreaTitleByeUpdate(float _DeltaTime, const StateInfo& _Info);
	void AreaTitleByeEnd(const StateInfo& _Info);
};

