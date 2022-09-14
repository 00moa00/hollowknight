#include "PreCompile.h"
#include "CameraGUI.h"

CameraGUI::CameraGUI() 
	:
	max_skew(0.0f),
	max_sway(1.5f),
	seed_shifting_factor(10.00f)
{
}

CameraGUI::~CameraGUI() 
{
}

void CameraGUI::Initialize(GameEngineLevel* _Level)
{

}

void CameraGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SameLine();
	ImGui::Text("CameraShaking");

	ImGui::SliderFloat("max_sway [pixel]", &max_sway, 0.0f, 64.0f);
	ImGui::SliderFloat("max_skew [degree]", &max_skew, 0.0f, 10.0f);
	ImGui::SliderFloat("seed_shifting_factor", &seed_shifting_factor, 0.0f, 20.f);

	
}

