#pragma once
#include "MasterPage.h"
#include "ItemSlot.h"

// Ό³Έν :
class InventoryPage : public MasterPage
{
public:
	// constrcuter destructer
	InventoryPage();
	~InventoryPage();

	// delete Function
	InventoryPage(const InventoryPage& _Other) = delete;
	InventoryPage(InventoryPage&& _Other) noexcept = delete;
	InventoryPage& operator=(const InventoryPage& _Other) = delete;
	InventoryPage& operator=(InventoryPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

public:
	void AllOff() override;
	void AllOn() override;

private:
	std::map<int, ItemSlot*> AllItem_;

};

