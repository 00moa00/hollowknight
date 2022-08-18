#pragma once
#include "MasterUI.h"

// Ό³Έν :
class BorderBottom : public MasterUI
{
public:
	// constrcuter destructer
	BorderBottom();
	~BorderBottom();

	// delete Function
	BorderBottom(const BorderBottom& _Other) = delete;
	BorderBottom(BorderBottom&& _Other) noexcept = delete;
	BorderBottom& operator=(const BorderBottom& _Other) = delete;
	BorderBottom& operator=(BorderBottom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

