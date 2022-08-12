#pragma once
#include "MasterUI.h"
// Ό³Έν :
class Soul : public MasterUI
{
public:
	// constrcuter destructer
	Soul();
	~Soul();

	// delete Function
	Soul(const Soul& _Other) = delete;
	Soul(Soul&& _Other) noexcept = delete;
	Soul& operator=(const Soul& _Other) = delete;
	Soul& operator=(Soul&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

