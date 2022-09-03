#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BorderArrow.h"
#include "BorderBottom.h"
#include "BorderCorner.h"
#include "BorderTop.h"

#include "SettingPointer.h"

#include "CharmPage.h"
#include "InventoryPage.h"
#include "MapPage.h"




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

	GameEngineUIRenderer* BackGround_;

	//CharmPage* CharmPage_;
	//InventoryPage* InventoryPage_;
	GameEngineFontRenderer* PageName_;

	SettingPointer* SettingPointer_;

	std::vector<MasterPage*> AllPage_;
	
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

	void SettingIdleStart(const StateInfo& _Info);
	void SettingIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SettingIdleEnd(const StateInfo& _Info);

	void SettingMoveRightStart(const StateInfo& _Info);
	void SettingMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void SettingMoveRightEnd(const StateInfo& _Info);

	void SettingMoveLeftStart(const StateInfo& _Info);
	void SettingMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void SettingMoveLeftEnd(const StateInfo& _Info);
};

