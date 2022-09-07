#pragma once
#include "MasterUI.h"
// Ό³Έν :
class ShopArrow : public MasterUI
{
public:
	// constrcuter destructer
	ShopArrow();
	~ShopArrow();

	// delete Function
	ShopArrow(const ShopArrow& _Other) = delete;
	ShopArrow(ShopArrow&& _Other) noexcept = delete;
	ShopArrow& operator=(const ShopArrow& _Other) = delete;
	ShopArrow& operator=(ShopArrow&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
private:

};

