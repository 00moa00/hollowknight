#pragma once
#include "MasterUI.h"
#include "SettingUIMaster.h"
#include "SettingPointerBox.h"

struct MoveState
{
	float4 Dir_;
	float4 Size_;
	std::string NextMoveStateName_;
};

class CharmSlot;
class HollowKnightLevel;
class PointActorComponent;

class SettingPointer : public MasterUI
{
public:
	// constrcuter destructer
	SettingPointer();
	~SettingPointer();

	// delete Function
	SettingPointer(const SettingPointer& _Other) = delete;
	SettingPointer(SettingPointer&& _Other) noexcept = delete;
	SettingPointer& operator=(const SettingPointer& _Other) = delete;
	SettingPointer& operator=(SettingPointer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool isMoveRenderer_;
	bool isMoveRendererDeath_;

	bool isDownNextPageRight_;
	bool isDownLextPageLeft_;

	bool inRightArrow_;
	bool inLeftArrow_;

	int Sort_;

	// 현재 인덱스
	int CurrentPosInCharmPage;
	int CurrentPosInMapPage;
	int CurrentPosInMonsterPage;
	int CurrentPosInInventoryPage;

	//총 인덱스
	int CharmPageActorCount;		// 부적은 맥스가 고정
	int MapPageActorCount;			
	int MonsterPageActorCount;

	float PointerMoveSpeed_;

	SettingPointerBox* SettingPointerBox_;

	PAGE_TYPE CurrentPage_; //현재 페이지
	PAGE_TYPE PrevPage_; // 페이지 저장용

	MoveState MoveState_;

	CharmSlot* CharmMovePointer_;

	GameEngineStateManager SettingPointerCharmPageManager_;
	GameEngineStateManager SettingPointerInventoryPageManager_;
	GameEngineStateManager SettingPointerMapPageManager_;

public:

	void PointerBoxRenderOn();
	void PointerBoxRenderOff();

	void AllOn();
	void AllOff();

	// 모든 포인터 액터들이 다 만들어지고 나서 사용해야하는 필수 함수
	//맥스 카운트 세팅
	void SetCharmPageActorMax();
	void SetMapPageActorMax();
	void SetMonsterBookActorMax();

	//페이지를 처음 켰을때 가장 먼저 있어야하는 포인터 위치
	void SetFirstPosCharmPage();


	void SetCurrentPage(PAGE_TYPE _PageType);

	//================================
	//    Bind State
	//================================


	//=========================================
	//    SettingPointerCharmPageManager
	//=========================================

	void PointerCharmPageMoveStart(const StateInfo& _Info);
	void PointerCharmPageMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageMoveEnd(const StateInfo& _Info);

	void PointerCharmPageIdleStart(const StateInfo& _Info);
	void PointerCharmPageIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageIdleEnd(const StateInfo& _Info);

	void PointerCharmPageMoveLeftStart(const StateInfo& _Info);
	void PointerCharmPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageMoveLeftEnd(const StateInfo& _Info);

	void PointerCharmPageMoveRightStart(const StateInfo& _Info);
	void PointerCharmPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageMoveRightEnd(const StateInfo& _Info);

	void PointerInCharmPageRightArrowStart(const StateInfo& _Info);
	void PointerInCharmPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInCharmPageRightArrowEnd(const StateInfo& _Info);

	void PointerCharmPageInLeftArrowStart(const StateInfo& _Info);
	void PointerCharmPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageInLeftArrowEnd(const StateInfo& _Info);

	void PointerCharmPageWaitStart(const StateInfo& _Info);
	void PointerCharmPageWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageWaitEnd(const StateInfo& _Info);

	void PointerChramPageSortSlotStart(const StateInfo& _Info);
	void PointerChramPageSortSlotUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerChramPageSortSlotEnd(const StateInfo& _Info);

	void PointerChramPageNextSortSlotStart(const StateInfo& _Info);
	void PointerChramPageNextSortSlotUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerChramPageNextSortSlotEnd(const StateInfo& _Info);

	void PointerChramPageMoveRendererMoveStart(const StateInfo& _Info);
	void PointerChramPageMoveRendererMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerChramPageMoveRendererMoveEnd(const StateInfo& _Info);


	//=========================================
	//    SettingPointerInventoryPageManager
	//=========================================

	void PointerInventoryPageMoveStart(const StateInfo& _Info);
	void PointerInventoryPageMoveUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageMoveEnd(const StateInfo& _Info);

	void PointerInventoryPageIdleStart(const StateInfo& _Info);
	void PointerInventoryPageIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageIdleEnd(const StateInfo& _Info);

	void PointerInventoryPageMoveLeftStart(const StateInfo& _Info);
	void PointerInventoryPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageMoveLeftEnd(const StateInfo& _Info);

	void PointerInventoryPageMoveRightStart(const StateInfo& _Info);
	void PointerInventoryPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageMoveRightEnd(const StateInfo& _Info);

	void PointerInInventoryPageRightArrowStart(const StateInfo& _Info);
	void PointerInInventoryPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInInventoryPageRightArrowEnd(const StateInfo& _Info);

	void PointerInventoryPageInLeftArrowStart(const StateInfo& _Info);
	void PointerInventoryPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageInLeftArrowEnd(const StateInfo& _Info);

	void PointerInventoryPageWaitStart(const StateInfo& _Info);
	void PointerInventoryPageWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageWaitEnd(const StateInfo& _Info);

	//=========================================
	//    SettingPointerMapPageManager
	//=========================================

	void PointerMapPageIdleStart(const StateInfo& _Info);
	void PointerMapPageIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageIdleEnd(const StateInfo& _Info);

	void PointerPageMoveLeftStart(const StateInfo& _Info);
	void PointerPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerPageMoveLeftEnd(const StateInfo& _Info);

	void PointerMapPageMoveRightStart(const StateInfo& _Info);
	void PointerMapPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageMoveRightEnd(const StateInfo& _Info);

	void PointerMapPageRightArrowStart(const StateInfo& _Info);
	void PointerMapPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageRightArrowEnd(const StateInfo& _Info);

	void PointerMapPageInLeftArrowStart(const StateInfo& _Info);
	void PointerMapPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageInLeftArrowEnd(const StateInfo& _Info);

	void PointerMapPageWaitStart(const StateInfo& _Info);
	void PointerMapPageWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageWaitEnd(const StateInfo& _Info);

	void PointerMapPageWideMapStart(const StateInfo& _Info);
	void PointerMapPageWideMapUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMapPageWideMapEnd(const StateInfo& _Info);

public:
	//================================
	//    Getter
	//================================
	bool GetisDownNextpageRight()
	{
		return isDownNextPageRight_;
	}

	bool GetisDownLextPageLeft()
	{
		return isDownLextPageLeft_;
	}


	//================================
	//    Setter
	//================================

	void SetisDownNextPageRight(bool _b)
	{
		isDownNextPageRight_ = _b;
	}
	
	void SetisDownNextPageLeft(bool _b)
	{
		isDownLextPageLeft_ = _b;
	}

};

