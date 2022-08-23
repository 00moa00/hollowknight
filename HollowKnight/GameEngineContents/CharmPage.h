#pragma once
#include "MasterUI.h"
#include "CharmSlot.h"
#include "Notches.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
// 설명 : 0~39 : 부적, 50, 51 : 포인터, 40~49 : 장착슬롯
class CharmPage : public MasterUI
{
public:
	// constrcuter destructer
	CharmPage();
	~CharmPage();

	// delete Function
	CharmPage(const CharmPage& _Other) = delete;
	CharmPage(CharmPage&& _Other) noexcept = delete;
	CharmPage& operator=(const CharmPage& _Other) = delete;
	CharmPage& operator=(CharmPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<CharmSlot*> AllCharmSlot_;
	std::vector<Notches*> AllNotes_;

	GameEngineFontRenderer* NotchesFont_;
	GameEngineUIRenderer* Line_;

public:
	void AllOff();
	void AllOn();

	void CreateEquippedCharm(GameEngineUIRenderer* _CopyRenderer);

};

