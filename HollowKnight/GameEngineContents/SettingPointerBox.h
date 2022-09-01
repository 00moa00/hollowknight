#pragma once
#include "MasterUI.h"


// Ό³Έν :
class SettingPointerBox : public MasterUI
{
public:
	// constrcuter destructer
	SettingPointerBox();
	~SettingPointerBox();

	// delete Function
	SettingPointerBox(const SettingPointerBox& _Other) = delete;
	SettingPointerBox(SettingPointerBox&& _Other) noexcept = delete;
	SettingPointerBox& operator=(const SettingPointerBox& _Other) = delete;
	SettingPointerBox& operator=(SettingPointerBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float ZommTimer_;

	float4 BoxSize_;

	GameEngineUIRenderer* LeftTopPointer_;
	GameEngineUIRenderer* RightTopPointer_;
	GameEngineUIRenderer* LeftBottomPointer_;
	GameEngineUIRenderer* RightBottomPointer_;

	GameEngineStateManager  SettingPointerBoxtManager_;

private:
	void PointerZoomInStart(const StateInfo& _Info);
	void PointerZoomInUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerZoomInEnd(const StateInfo& _Info);

	void PointerZoomOutStart(const StateInfo& _Info);
	void PointerZoomOutUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerZoomOutEnd(const StateInfo& _Info);

	void SetPositiveY(GameEngineUIRenderer* _GameEngineUIRenderer);

public:
	void SetBoxSize(float4 _Size);
	void AllPointerOn();
	void AllPointerOff();
};

