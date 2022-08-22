#pragma once
#include "MasterUI.h"

// Ό³Έν :
class AreaTitleTop : public MasterUI
{
public:
	// constrcuter destructer
	AreaTitleTop();
	~AreaTitleTop();

	// delete Function
	AreaTitleTop(const AreaTitleTop& _Other) = delete;
	AreaTitleTop(AreaTitleTop&& _Other) noexcept = delete;
	AreaTitleTop& operator=(const AreaTitleTop& _Other) = delete;
	AreaTitleTop& operator=(AreaTitleTop&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

