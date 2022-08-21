#pragma once
#include "MasterUI.h"
#include "CharmSlot.h"

// Ό³Έν :
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

public:
	void AllOff();
	void AllOn();



};

