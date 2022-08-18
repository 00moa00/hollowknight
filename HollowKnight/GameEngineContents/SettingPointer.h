#pragma once
#include "MasterUI.h"

// Ό³Έν :
class SettingPointer : public MasterUI
{
public:
	// constrcuter destructer
	SettingPointer();
	~SettingPointer();

	// delete Function
	SettingPointer(const SettingPointer& _Other) = delete;
	SettingPointer(SettingPointer&& _Other) noexcept = delete;
	SettingPointer& operator=(const SettingPointer& _Other) = delete;
	SettingPointer& operator=(SettingPointer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

