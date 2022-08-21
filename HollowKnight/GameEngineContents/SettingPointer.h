#pragma once
#include "MasterUI.h"
#include "SettingUIMaster.h"
#include "SettingPointerBox.h"

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

	bool inRightArrow_;
	bool inLeftArrow_;

	// 현재 인덱스
	int CurrentPosInCharmPage;
	int CurrentPosInMapPage;
	int CurrentPosInCMonsterPage;

	//총 인덱스
	int CharmPageActorCount;
	int MapPageActorCount;
	int MonsterPageActorCount;

	SettingPointerBox* SettingPointerBox_;

	GameEngineStateManager SettingPointeManager_;
public:

	void AllOn();
	void AllOff();

	// 모든 포인터 액터들이 다 만들어지고 나서 사용해야하는 필수 함수

	//맥스 카운트 세팅
	void SetCharmPageActorMax();
	void SetMapPageActorMax();
	void SetMonsterBookActorMax();

	//페이지를 처음 켰을때 가장 먼저 있어야하는 포인터 위치
	void SetFirstPosCharmPage();
	void SetFirstPosMapPage();
	void SetFirstPosMonsterBookPage();

	//================================
	//    Bind State
	//================================


	void PointerIdleStart(const StateInfo& _Info);
	void PointerIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerIdleEnd(const StateInfo& _Info);

	void PointerMoveLeftStart(const StateInfo& _Info);
	void PointerMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMoveLeftEnd(const StateInfo& _Info);

	void PointerMoveRightStart(const StateInfo& _Info);
	void PointerMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMoveRightEnd(const StateInfo& _Info);

	void PointerInRightArrowStart(const StateInfo& _Info);
	void PointerInRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInRightArrowEnd(const StateInfo& _Info);

	void PointerInLeftArrowStart(const StateInfo& _Info);
	void PointerInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInLeftArrowEnd(const StateInfo& _Info);

};

