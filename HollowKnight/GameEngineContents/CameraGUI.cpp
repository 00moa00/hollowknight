#include "PreCompile.h"
#include "CameraGUI.h"

CameraGUI::CameraGUI() 
	:
	MaxSkew(0.2f),
	MaxSway(1.5f),
	SeedShiftingFactor(10.00f)
{
}

CameraGUI::~CameraGUI() 
{
}

void CameraGUI::Initialize(GameEngineLevel* _Level)
{
	MaxSkew = KnightData::GetInst()->GetMaxSkew();
	MaxSway = KnightData::GetInst()->GetMaxSway();
	SeedShiftingFactor = KnightData::GetInst()->GetSeedshiftingFactor();
}

void CameraGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SameLine();
	ImGui::Text("CameraShaking");

	ImGui::SliderFloat("MaxSway [pixel]", &MaxSway, 0.0f, 64.0f);
	ImGui::SliderFloat("MaxSkew [degree]", &MaxSkew, 0.0f, 10.0f);
	ImGui::SliderFloat("SeedShiftingFactor", &SeedShiftingFactor, 0.0f, 20.f);

	
}

