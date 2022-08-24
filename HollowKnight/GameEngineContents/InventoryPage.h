#pragma once
#include "MasterPage.h"

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

private:

};

