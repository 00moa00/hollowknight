#pragma once
#include "MasterUI.h"

// Ό³Έν :
class BorderArrow : public MasterUI
{
public:
	// constrcuter destructer
	BorderArrow();
	~BorderArrow();

	// delete Function
	BorderArrow(const BorderArrow& _Other) = delete;
	BorderArrow(BorderArrow&& _Other) noexcept = delete;
	BorderArrow& operator=(const BorderArrow& _Other) = delete;
	BorderArrow& operator=(BorderArrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

