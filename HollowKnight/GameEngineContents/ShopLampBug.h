#pragma once
#include "MasterEffect.h"

// Ό³Έν :
class ShopLampBug : public MasterEffect
{
public:
	// constrcuter destructer
	ShopLampBug();
	~ShopLampBug();

	// delete Function
	ShopLampBug(const ShopLampBug& _Other) = delete;
	ShopLampBug(ShopLampBug&& _Other) noexcept = delete;
	ShopLampBug& operator=(const ShopLampBug& _Other) = delete;
	ShopLampBug& operator=(ShopLampBug&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

