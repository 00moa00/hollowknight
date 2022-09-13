#include "PreCompile.h"
#include "CameraGUI.h"

CameraGUI::CameraGUI() 
{
}

CameraGUI::~CameraGUI() 
{
}

void CameraGUI::Initialize(GameEngineLevel* _Level)
{
	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);

}

void CameraGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SameLine();
	ImGui::Text("CameraShaking");
}

