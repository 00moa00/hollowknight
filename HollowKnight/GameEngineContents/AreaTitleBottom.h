#pragma once
#include "MasterUI.h"



// Ό³Έν :
class AreaTitleBottom : public MasterUI
{
public:
	// constrcuter destructer
	AreaTitleBottom();
	~AreaTitleBottom();

	// delete Function
	AreaTitleBottom(const AreaTitleBottom& _Other) = delete;
	AreaTitleBottom(AreaTitleBottom&& _Other) noexcept = delete;
	AreaTitleBottom& operator=(const AreaTitleBottom& _Other) = delete;
	AreaTitleBottom& operator=(AreaTitleBottom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

