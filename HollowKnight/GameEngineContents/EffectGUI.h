#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "KnightData.h"
// Ό³Έν :
class EffectGUI : public GameEngineGUIWindow
{
public:
	// constrcuter destructer
	EffectGUI();
	~EffectGUI();

	// delete Function
	EffectGUI(const EffectGUI& _Other) = delete;
	EffectGUI(EffectGUI&& _Other) noexcept = delete;
	EffectGUI& operator=(const EffectGUI& _Other) = delete;
	EffectGUI& operator=(EffectGUI&& _Other) noexcept = delete;
protected:
	void Initialize(class GameEngineLevel* _Level) override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


private:
	static ImVec4 Overlaycolor;
	static ImVec4 saved_palette[32];

	//static ImVec4 color;

	bool overlay_flag;
	bool alpha_half_preview ;
	bool drag_and_drop ;
	bool options_menu;
	bool hdr;
	bool saved_palette_init;

public:
	float4 GetColor()
	{
		float4 ReturnColor;
		
		ReturnColor.x = Overlaycolor.x;
		ReturnColor.y = Overlaycolor.y;
		ReturnColor.z = Overlaycolor.z;
		ReturnColor.w = Overlaycolor.w;

		return ReturnColor;
	}

	bool GetOverlayFlag()
	{
		return overlay_flag;
	}

	void EffectGUIDeath()
	{
		float4 ReturnColor;

		ReturnColor.x = Overlaycolor.x;
		ReturnColor.y = Overlaycolor.y;
		ReturnColor.z = Overlaycolor.z;
		ReturnColor.w = Overlaycolor.w;
		KnightData::GetInst()->SetOverlayColor(ReturnColor);
		
		this->Death();
	}




};

 