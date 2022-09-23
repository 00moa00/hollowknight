#pragma once
#include <GameEngineCore/GameEngineGUI.h>
#include "KnightData.h"
// 설명 :
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
	ImVec4 Overlaycolor;
	 
	bool isBlendClick_;

	bool overlay_flag;

	//bool saved_palette_init;

	int MainLightitemsCurrent;
	int SiblingLightitemsCurrent;
	int DonutLightitemsCurrent;

	bool isMainLightOnOff_;
	bool isSiblingLightOnOff_;
	bool isDonutLightOnOff_;


	ImVec4 MainLightMulColor_;				//메인 라이트 컬러
	ImVec4 MainLightPlusColor_;				//메인 라이트 플러스 컬러

	ImVec4 SlibingLightMulColor_;
	ImVec4 SlibingLightPlusColor_;

	ImVec4 DounutLightMulColor_;
	ImVec4 DounutLightPlusColor_;

	//bool 
private:




	ImVec4& ConvertFromFloat4(ImVec4 _Im, float4 f4)
	{
		_Im.x = f4.x;
		_Im.y = f4.y;
		_Im.z = f4.z;
		_Im.w = f4.w;

		return _Im;
	}

	float4& ConvertToFloat4(float4 f4, ImVec4 _Im)
	{
		f4.x = _Im.x;
		f4.y = _Im.y;
		f4.z = _Im.z;
		f4.w = _Im.w;

		return f4;
	}

public:

	bool GetisMainLightOnOff() const
	{
		return isMainLightOnOff_;
	}

	bool GetisSiblingLightOnOff() const
	{
		return isSiblingLightOnOff_;
	}

	bool GetisDonutLightOnOff() const
	{
		return isDonutLightOnOff_;
	}


	float4 GetColor()
	{
		float4 ReturnColor;
		
		ReturnColor.x = Overlaycolor.x;
		ReturnColor.y = Overlaycolor.y;
		ReturnColor.z = Overlaycolor.z;
		ReturnColor.w = Overlaycolor.w;



		return ReturnColor;
		//ReturnColor.x = Overlaycolor.x;
		//return ConvertToFloat4(ReturnColor, Overlaycolor);

	}

	bool GetOverlayFlag()
	{
		return overlay_flag;
	}

	void EffectGUIDeath()
	{
		float4 ReturnColor;

		ReturnColor = ConvertToFloat4(ReturnColor, Overlaycolor);
		KnightData::GetInst()->SetOverlayColor(ReturnColor);
		
		this->Death();
	}

	float4 GetoverlayColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, Overlaycolor);

	}

	BlendMode GetMainLightitemsCurrent()
	{
		return static_cast<BlendMode>(MainLightitemsCurrent);
	}

	BlendMode GetSiblingLightitemsCurrent()
	{
		return static_cast<BlendMode>(SiblingLightitemsCurrent);
	}

	BlendMode GetDonutLightitemsCurrent()
	{
		return static_cast<BlendMode>(DonutLightitemsCurrent);
	}

	float4 GetMainLightMulColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, MainLightMulColor_);

	}

	float4 GetMainLightPlusColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, MainLightPlusColor_);
	}

	float4 GetSlibingLightMulColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, SlibingLightMulColor_);
	}

	float4 GetSlibingLightPlusColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, SlibingLightPlusColor_);
	}

	float4 GetDounutLightMulColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, DounutLightMulColor_);
	}

	float4 GetDounutLightPlusColor()
	{
		float4 ReturnColor;
		return ConvertToFloat4(ReturnColor, DounutLightPlusColor_);
	}



};

 