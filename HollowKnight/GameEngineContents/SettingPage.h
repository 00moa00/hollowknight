#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BorderArrow.h"
#include "BorderBottom.h"
#include "BorderCorner.h"
#include "BorderTop.h"

#include "CharmPage.h"

class GameEngineTextureRenderer;
class SettingPage : public GameEngineActor
{
public:
	// constrcuter destructer
	SettingPage();
	~SettingPage();

	// delete Function
	SettingPage(const SettingPage& _Other) = delete;
	SettingPage(SettingPage&& _Other) noexcept = delete;
	SettingPage& operator=(const SettingPage& _Other) = delete;
	SettingPage& operator=(SettingPage&& _Other) noexcept = delete;

protected:
	void Start()override;
	void Update(float _DeltaTime)override;

private:
	bool OnOffPage_;


	BorderCorner* BorderCornerLeftTop_;
	BorderCorner* BorderCornerRightTop_;
	BorderCorner* BorderCornerLeftBottom_;
	BorderCorner* BorderCornerRightBottom_;

	BorderBottom* BorderBottom_;

	BorderTop* BorderTop_;

	BorderArrow* BorderLeftArrow_;
	BorderArrow* BorderRightArrow_;

	CharmPage* CharmPage_;
	GameEngineUIRenderer* BackGround_;

	GameEngineStateManager SettingPageManager_;


private:
	void OnOffPage();
	void AllOff();
	void AllOn();

	//================================
	//    Bind State
	//================================

	void SettingOffStart(const StateInfo& _Info);
	void SettingOffUpdate(float _DeltaTime, const StateInfo& _Info);
	void SettingOffEnd(const StateInfo& _Info);

	void SettingOnStart(const StateInfo& _Info);
	void SettingOnUpdate(float _DeltaTime, const StateInfo& _Info);
	void SettingOnEnd(const StateInfo& _Info);


};

